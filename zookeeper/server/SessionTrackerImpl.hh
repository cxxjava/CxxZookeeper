/*
 * SessionTrackerImpl.hh
 *
 *  Created on: 2017-11-22
 *      Author: cxxjava@163.com
 */

#ifndef SessionTrackerImpl_HH_
#define SessionTrackerImpl_HH_

#include "Efc.hh"

#include "./ZooTrace.hh"
#include "./SessionTracker.hh"
#include "./ZooKeeperCriticalThread.hh"
#include "./ZooKeeperServerListener.hh"
#include "../KeeperException.hh"
#include "../common/TimeUtils.hh"

namespace efc {
namespace ezk {

/**
 * This is a full featured SessionTracker. It tracks session in grouped by tick
 * interval. It always rounds up the tick interval to provide a sort of grace
 * period. Sessions are thus expired in batches made up of sessions that expire
 * in a given interval.
 */

class SessionImpl : public Session {
public:
	SessionImpl(llong sessionId, int timeout, llong expireTime) {
		this->sessionId = sessionId;
		this->timeout = timeout;
		this->tickTime = expireTime;
		isClosing_ = false;
	}

	llong sessionId;
	int timeout;
	llong tickTime;
	boolean isClosing_;

	sp<EObject> owner;

	virtual llong getSessionId() { return sessionId; }
	virtual int getTimeout() { return timeout; }
	virtual boolean isClosing() { return isClosing_; }
};

class SessionSet : public EObject {
public:
	EHashSet<sp<SessionImpl> > sessions;// = new HashSet<SessionImpl>();
};

class SessionTrackerImpl : public ZooKeeperCriticalThread, virtual public SessionTracker {
public:
	SessionTrackerImpl(sp<SessionExpirer> expirer,
            EConcurrentHashMap<llong, EInteger>* sessionsWithTimeout, int tickTime,
            llong sid, ZooKeeperServerListener* listener);

    virtual void dumpSessions(EPrintStream* pwriter);

    virtual EString toString();

	virtual void run();

    boolean touchSession(llong sessionId, int timeout);

    void setSessionClosing(llong sessionId);

    void removeSession(llong sessionId);

    void shutdown();

    llong createSession(int sessionTimeout);

    void addSession(llong id, int sessionTimeout);

    void checkSession(llong sessionId, sp<EObject> owner) THROWS2(SessionExpiredException, SessionMovedException);

    void setOwner(llong id, sp<EObject> owner) THROWS(SessionExpiredException);

    static llong initializeNextSession(llong id);

private:

    static sp<ELogger> LOG;// = LoggerFactory.getLogger(SessionTrackerImpl.class);

    EHashMap<llong, sp<SessionImpl> > sessionsById;// = new HashMap<Long, SessionImpl>();

    EHashMap<llong, SessionSet*> sessionSets;// = new HashMap<Long, SessionSet>();

    EConcurrentHashMap<llong, EInteger>* sessionsWithTimeout;
    llong nextSessionId;// = 0;
    llong nextExpirationTime;

    int expirationInterval;

    sp<SessionExpirer> expirer;

    volatile boolean running = true;

    volatile llong currentTime;

    llong roundToInterval(llong time) {
        // We give a one interval grace period
        return (time / expirationInterval + 1) * expirationInterval;
    }
};

} /* namespace ezk */
} /* namespace efc */
#endif /* SessionTrackerImpl_HH_ */

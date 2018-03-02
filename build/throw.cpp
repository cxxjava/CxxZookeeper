#include <functional>

namespace std {
	void __throw_bad_function_call() {throw -1; /*bad_function_call("invalid function called");*/}
}


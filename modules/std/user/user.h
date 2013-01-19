#ifndef CLEVER__USER_H
#define CLEVER__USER_H

namespace clever {

class UserModule: public Module {
public:
	UserModule()
		: Module("_user") {}

	~UserModule() {}

	void init() {}
};

} // clever

#endif

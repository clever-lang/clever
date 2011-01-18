#ifndef CLEVER_PKGMANAGER_H
#define CLEVER_PKGMANAGER_H

#include <boost/unordered_map.hpp>
#include "module.h"

namespace clever {

/**
 * Function table
 */
typedef boost::unordered_map<const std::string, FunctionPtr> FunctionTable;

class CString;

typedef boost::unordered_map<const CString*, Package*> PackageMap;
typedef std::pair<const CString*, Package*> PackagePair;

class PackageManager {
public:
	PackageManager() { }

	~PackageManager() { }

	/**
	 * Load package map
	 */
	void Init(FunctionTable*) throw();
	/**
	 * Free memory
	 */
	void shutdown() throw();
	/**
	 * Add a package to list
	 */
	void addPackage(const CString* name, Package* package) throw() {
		m_packages.insert(PackagePair(name, package));
	}
	/**
	 * Load an specific package
	 */
	void loadPackage(const CString*) throw();
	/**
	 * Load an specific package module
	 */
	void loadModule(const CString*, const CString*) throw();
	void loadModule(Module*) throw();
private:
	PackageMap m_packages;

	FunctionTable* m_ftable;
};

} // clever

#endif // CLEVER_PKGMANAGER_H
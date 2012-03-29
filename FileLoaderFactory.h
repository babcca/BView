#ifndef FILELOADERFACTORY_H
#define FILELOADERFACTORY_H
#include <map>
#include <functional>
#include "fileloader.h"
/**
 * @struct FileLoaderFactory
 * Podle registrovane koncovky zavola k ni pridruzeny funktor,
 * ktery se stara o vytvoreni spravne instance loaderu.
 */
struct FileFactory {
    /** @typedef Predek vsech file loaderu */
    typedef FileLoader * BaseLoader;
    /** @typedef Funktor, ktery se stara o vytvoreni instance */
    typedef std::function<BaseLoader (void)> Factory;
    /** @typedef Uloziste koncovky a funktoru */
    typedef std::map<std::string, Factory> Storage;
    /** Uloziste koncovky a funktoru */
    Storage factoryStorage;

    /**
     * Zaregistruje k dane koncovce jeji tovarnu na vytvareni instanci
     * @param std::string extension Registrovana koncovka
     * @param Factory factory Funktor pro vytvoreni instance
     */
    void AddFactory(std::string extension, Factory factory) {
        factoryStorage[extension] = factory;
    }

    /**
     * Pokud je zadana koncovka souboru zaregistrovana
     * vrati instanci loaderu pro dany typ souboru nebo null
     * @param std::string extension Hledana koncovka
     * @return @typedef BaseLoader
     */
    BaseLoader operator[] (const std::string & extension) {
        Storage::const_iterator factory = factoryStorage.find(extension);
        if (factory != factoryStorage.end()) { return factory->second(); }
        else { return 0; }
    }
};
#endif // FILELOADERFACTORY_H

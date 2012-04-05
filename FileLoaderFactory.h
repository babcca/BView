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
template<typename BaseLoader>
struct FileFactory {
    /** @typedef Predek vsech file loaderu */
    typedef BaseLoader Loader;
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
    void AddFactory(const std::string & extension, Factory factory) {
        factoryStorage[extension] = factory;
    }

    /**
     * Pokud je zadana koncovka souboru zaregistrovana
     * vrati instanci loaderu pro dany typ souboru nebo null
     * @param std::string extension Hledana koncovka
     * @return BaseLoader * Instance loaderu
     */
    BaseLoader GetLoader(const std::string & extension) const {
        if (IsRegistred(extension)) { return factoryStorage.find(extension)->second(); }
        else { return 0; }
    }
    /**
     * Kontroluje jestli je zadan koncovka registrovana
     * @param std::string extension Hledana koncovka
     * @return bool
     */
    bool IsRegistred(const std::string & extension) const {
        Storage::const_iterator factory = factoryStorage.find(extension);
        return factory != factoryStorage.end();
    }
};
#endif // FILELOADERFACTORY_H

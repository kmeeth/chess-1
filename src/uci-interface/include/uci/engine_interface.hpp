#ifndef UCI_ENGINE_INTERFACE_HPP
#define UCI_ENGINE_INTERFACE_HPP

#include <uci/limits.hpp>
#include <uci/config.hpp>

#include <string>
#include <sstream>
#include <iostream>
#include <iterator>

namespace uci {

class engine_interface {
   public:
    /**
     * Return whether the automatic register check was passed
     */
    virtual bool check_register(void);

    /**
     * Return true if registration is successful
     */
    virtual bool check_register(const std::string &user,
                                const std::string &code) = 0;
    /**
     * Returns true if copy protection OK
     */
    virtual bool check_copy_protection(void);

    /**
     * Loads default options
     */
    [[nodiscard]] virtual bool load_options(void);

    /**
     * The following are metadata functions
     */
    void set_author_name(const char *name);
    void set_engine_name(const char *name);
    void requires_registration(bool v);
    void requires_copy_protection(bool v);
    void can_ponder(bool v);

    /**
     * Updates the position the engine holds
     */
    virtual void update_position(const std::string &fen,
                                 const std::string &moves) = 0;
    /*
     * Returns the best move in UCI format
     */
    virtual std::string get_best_move(const limits &l) = 0;

    /*
     * Sets the engine to ponder mode
     */
    [[nodiscard]] virtual bool ponder_mode(void) = 0;

    /*
     * Sets the engine to search mode
     */
    [[nodiscard]] virtual bool search_mode(void) = 0;

    /*
    * Runs the engine
    */
    void run(void);

    /*
    * Main engine loop
    */
    void loop(void);

    virtual ~engine_interface() = default;
    engine_interface(const engine_interface& other) = delete;
    engine_interface(engine_interface&& other) = delete;
    engine_interface& operator=(const engine_interface& other) = delete;
    engine_interface& operator=(engine_interface&& other) = delete;

    /**
     * Will ignore all input until given a `quit` command
     */
    static void do_nothing_loop(void);

    /**
     * Will tell the GUI the options that it can modify
     */
    static void enlist_options(void);

    /**
     * Will check for registration if needed. If it returns false then the
     * engine shouldnt work properly. (It will enter the `do_nothing_loop`)
     */
    bool check_registration_if_required(void);

    /**
     * Will check for copyprotection if needed. If it returns false then the
     * engine shouldnt work properly. (It will enter the `do_nothing_loop`)
     */
    bool check_copy_protection_if_required(void);


   private:
    const char* author_name = nullptr;
    const char* engine_name = nullptr;
    bool engine_requires_registration = false;
    bool engine_requires_copyprotection = false;
    bool engine_can_ponder = false;
};

} // namespace uci

#endif


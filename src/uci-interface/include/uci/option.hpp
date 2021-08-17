#ifndef UCI_INTERFACE_OPTION_HPP
#define UCI_INTERFACE_OPTION_HPP

#include <stdexcept>
#include <string>
#include <cstdint>
#include <vector>
#include <exception>
#include <initializer_list>

namespace uci {

/**
 * The types the options can be
 */
enum class option_types {
    check,
    spin,
    combo,
    button,
    string
};

/**
 * @return A string representation of the given option
 */
std::string describe(option_types o);

/**
 * The options that can be set by the GUI to configure the behaviour of the
 * engine
 */
class option {
   public:
    using call_back_t = void (*)(const option&);

    template<option_types type>
    [[nodiscard]] auto as(void) const;

    template<>
    [[nodiscard]] auto as<option_types::check>(void) const {
        throw_on_wrong_type(option_types::check);
        return ((value == "True") || value == "true");
    }

    template<>
    [[nodiscard]] auto as<option_types::spin>(void) const {
        throw_on_wrong_type(option_types::spin);
        return std::stoi(value);
    }

    template<>
    [[nodiscard]] auto as<option_types::combo>(void) const {
        throw_on_wrong_type(option_types::combo);
        return value;
    }

    template<>
    [[nodiscard]] auto as<option_types::string>(void) const {
        throw_on_wrong_type(option_types::string);
        return value;
    }

    /**
     * For an option of type `check`
     */
    explicit option(bool val, call_back_t on_change = nullptr);

    /**
     * For an option type `spin`
     */
    explicit option(int64_t val, call_back_t on_change = nullptr);

    /**
     * For an option type `combo`
     */
    option(std::string                        default_value,
           std::initializer_list<std::string> others,
           call_back_t                        on_change = nullptr);

    /**
     * For an option type `button`
     */
    explicit option(call_back_t on_change);

    /**
     * For an option type `string`
     */
    explicit option(std::string val, call_back_t on_change = nullptr);

   private:
    option_types type;
    std::string value;
    std::vector<std::string> combo_values;
    call_back_t call_back = nullptr;

    void throw_on_wrong_type(option_types expected) const;
};


} // namespace uci

#endif

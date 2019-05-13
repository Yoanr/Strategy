#include <iostream>

class Lambda
{
public:
    template <typename Lambda>
    struct convert_lambda : convert_lambda<decltype(&Lambda::operator())>
    {
    };
    template <typename Lambda, typename ReType, typename... Args>
    struct convert_lambda<ReType (Lambda::*)(Args...) const>
    {
        using funPtr = ReType (*)(Args...);
        static funPtr make_function_ptr(const Lambda &t)
        {
            static const Lambda &lmda = t;
            return [](Args... args) { return lmda(args...); };
        }
    };
    template <typename Lambda>
    using convert_lambda_t = typename convert_lambda<Lambda>::funPtr;
    template <typename Lambda>
    static constexpr convert_lambda_t<Lambda> make_function_ptr(const Lambda &t)
    {
        return convert_lambda<Lambda>::make_function_ptr(t);
    }
};
  #pragma once

  #include <exception>
  #include <iostream>
  #include <string>

  class NotImplementedException : public std::logic_error {
  public:
    NotImplementedException(std::string const& message = "Functionality not yet implemented") : std::logic_error(message) {}
  };

  namespace Akr {
  // Define a type trait to check if T is derived from specified type U
  template <typename T, typename U>
  struct IsDerivedFrom {
    static constexpr bool value = std::is_base_of_v<U, T>;
  };

  }  // namespace Akr

  /**
  * @brief Macro to enable SFINAE (Substitution Failure Is Not An Error) technique to check if a type is derived from another type.
  *
  * This macro defines a template specialization that enables SFINAE (Substitution Failure Is Not An Error) to check if a type T is derived from the specified type Type.
  * It relies on the IsDerivedFrom type trait to determine if T is derived from Type.
  *
  * Example Usage:
  * \code{.cpp}
  * IS_CHILD_OF_TYPE_T(BaseType)
  * \endcode
  *
  * @param Type The base type to check if T is derived from.
  * @note This macro should be used before defining a template function or class where the template parameter T needs to be checked if it's derived from a specific base type.
  * @note This macro uses std::enable_if to perform the type checking at compile-time.
  */
  #define IS_CHILD_OF_TYPE_T(Type) template <typename T, typename = typename std::enable_if<Akr::IsDerivedFrom<T, Type>::value>::type>

/**
 * @brief Macro to enable SFINAE (Substitution Failure Is Not An Error) technique to check if a type is derived from another type with additional template arguments.
 *
 * This macro is an extension of IS_CHILD_OF_T macro and allows specifying additional template arguments for the derived type T.
 *
 * Example Usage:
 * \code{.cpp}
 * IS_CHILD_OF_TYPE_ARGS_T(BaseType, Args...)
 * \endcode
 *
 * @param Type The base type to check if T is derived from.
 * @param Args Additional template arguments for the derived type T.
 * @note This macro should be used before defining a template function or class where the template parameter T needs to be checked if it's derived from a specific base type with additional template arguments.
 * @note This macro uses std::enable_if to perform the type checking at compile-time.
 */
#define IS_CHILD_OF_TYPE_ARGS_T(Type) template <typename T, typename... Args, std::enable_if_t<Akr::Common::IsDerivedFromV<T, Type>::value, int> = 0>

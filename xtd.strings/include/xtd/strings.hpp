/// @file
/// @brief Contains xtd::strings class.
#pragma once

#include "__format.hpp"
#include "string_split_options.hpp"

#include <algorithm>
#include <locale>
#include <sstream>
#include <string>
#include <vector>

/// @brief The xtd namespace contains all fundamental classes to access console.
namespace xtd {
  /// @brief The strings Cainteins string operation methods.
  class strings {
  public:
    /// @cond
    strings() = delete;
    /// @endcond

    /// @brief Compares two specified String objects.
    /// @param str_a The first String.
    /// @param str_b The second String.
    /// @return int32 A 32-bit signed integer that indicates the relative order of the objects being compared. The return value has these meanings:
    /// @return Less than zero      str_a is less than str_b.
    /// @return Zero                str_a is equal to str_b.
    /// @return Greater than zero   str_a is greater than str_b.
    template<typename Char>
    static int compare(const std::basic_string<Char>& str_a, const std::basic_string<Char>& str_b) {return compare(str_a, str_b, false);}
    
    /// @brief Compares two specified String objects, ignoring or honoring their case.
    /// @param str_a The first String.
    /// @param str_b The second String.
    /// @param ignore_case A bool indicating a case-sensitive or insensitive comparison. (true indicates a case-insensitive comparison.)
    /// @return int32 A 32-bit signed integer that indicates the relative order of the objects being compared. The return value has these meanings:
    /// @return Less than zero      str_a is less than str_b.
    /// @return Zero                str_a is equal to str_b.
    /// @return Greater than zero   str_a is greater than str_b.
    template<typename Char>
    static int compare(const std::basic_string<Char>& str_a, const std::basic_string<Char>& str_b, bool ignore_case) {
      if (ignore_case)
        return to_lower(str_a).compare(to_lower(str_b));
      return str_a.compare(str_b);
    }
    
    /// @brief Compares substrings of two specified String objects.
    /// @param str_a The first String.
    /// @param index_a The position of the substring within str_a.
    /// @param str_b The second String.
    /// @param index_b The position of the substring within str_b.
    /// @param length The maximum number of characters in the substrings to compare
    /// @return int32 A 32-bit signed integer that indicates the relative order of the objects being compared. The return value has these meanings:
    /// @return Less than zero      str_a is less than str_b.
    /// @return Zero                str_a is equal to str_b.
    /// @return Greater than zero   str_a is greater than str_b.
    template<typename Char>
    static int compare(const std::basic_string<Char>& str_a, size_t index_a, const std::basic_string<Char>& str_b, size_t index_b, size_t length) {return compare(str_a, index_a, str_b, index_b, length, false);}
    
    /// @brief Compares substrings of two specified String objects, ignoring or honoring their case.
    /// @param str_a The first String.
    /// @param index_a The position of the substring within str_a.
    /// @param str_b The second String.
    /// @param index_b The position of the substring within str_b.
    /// @param length The maximum number of characters in the substrings to compare
    /// @param ignore_case A bool indicating a case-sensitive or insensitive comparison. (true indicates a case-insensitive comparison.)
    /// @return int32 A 32-bit signed integer that indicates the relative order of the objects being compared. The return value has these meanings:
    /// @return Less than zero      str_a is less than str_b.
    /// @return Zero                str_a is equal to str_b.
    /// @return Greater than zero   str_a is greater than str_b.
    template<typename Char>
    static int compare(const std::basic_string<Char>& str_a, size_t index_a, const std::basic_string<Char>& str_b, size_t index_b, size_t length, bool ignore_case) {
      std::basic_string<Char> sa(str_a.substr(index_a, length));
      std::basic_string<Char> sb(str_b.substr(index_b, length));
      if (ignore_case)
        return to_lower(sa).compare(to_lower(sb));
      return sa.compare(sb);
    }
    
    /// @brief Concatenates the String representations of the elements in a specified Args.
    /// @param args Variadic tempalte arguments to concat.
    /// @return string The concatenated string representations of the values of the elements in args.
    template<typename Char, typename ... Args>
    static std::basic_string<Char> concat(Args&& ... args) noexcept {
      std::stringstream ss;
      int unpack[] {0, (ss << args, 0)...};
      static_cast<void>(unpack);
      return ss.str();
    }

    /// @brief Returns a value indicating whether the specified String object occurs within this String.
    /// @param value The first String.
    /// @return bool true if the value parameter occurs within this String, or if value is the empty String (""); otherwise, false
    template<typename Char>
    static bool contains(const std::basic_string<Char>& str, const std::basic_string<Char>& value) noexcept {
      return str.find(value) != str.npos;
    }
    
    /// @cond
    template<typename Char>
    static bool contains(const std::basic_string<Char>& str, const Char* value) noexcept {return contains(str, std::basic_string<Char>(value));}
    template<typename Char>
    static bool contains(const Char* str, const std::basic_string<Char>& value) noexcept {return contains(std::basic_string<Char>(str), value);}
    template<typename Char>
    static bool contains(const Char* str, const Char* value) noexcept {return contains(std::basic_string<Char>(str), std::basic_string<Char>(value));}
    /// @endcond

    /// @brief Determines whether the end of this instance matches the specified String.
    /// @param value A String to compare to.
    /// @return bool true if value matches the end of this instance; otherwise, false.
    /// @remarks This method compares value to the substring at the end of this instance that is the same length as value, and returns an indication whether they are equal. To be equal, value must be a reference to this same instance, or match the end of this instance.
    template<typename Char>
    static bool ends_width(const std::basic_string<Char>& str, const std::basic_string<Char>& value) noexcept {return ends_width(str, value, false);}
    
    /// @brief Determines whether the end of this instance matches the specified String, ignoring or honoring their case.
    /// @param value A String to compare to.
    /// @param ignore_case true to ignore case when comparing this instance and value; otherwise, false
    /// @return bool true if value matches the end of this instance; otherwise, false.
    /// @remarks This method compares value to the substring at the end of this instance that is the same length as value, and returns an indication whether they are equal. To be equal, value must be a reference to this same instance, or match the end of this instance.
    template<typename Char>
    static bool ends_width(const std::basic_string<Char>& str, const std::basic_string<Char>& value, bool ignore_case) noexcept {
      if (ignore_case)
        return to_lower(str).rfind(to_lower(value)) - to_lower(value).size() == 0;
      return str.rfind(value) - value.size() == 0;
    }
    
    /// @cond
    template<typename Char>
    static bool ends_width(const std::basic_string<Char>& str, const Char* value) noexcept {return ends_width(str, std::basic_string<Char>(value), false);}
    template<typename Char>
    static bool ends_width(const Char* str, const std::basic_string<Char>& value) noexcept {return ends_width(std::basic_string<Char>(str), value, false);}
    template<typename Char>
    static bool ends_width(const Char* str, const Char* value) noexcept {return ends_width(std::basic_string<Char>(str), std::basic_string<Char>(value), false);}

    template<typename Char>
    static bool ends_width(const std::basic_string<Char>& str, const Char* value, bool ignore_case) noexcept {return ends_width(str, std::basic_string<Char>(value), ignore_case);}
    template<typename Char>
    static bool ends_width(const Char* str, const std::basic_string<Char>& value, bool ignore_case) noexcept {return ends_width(std::basic_string<Char>(str), value, ignore_case);}
    template<typename Char>
    static bool ends_width(const Char* str, const Char* value, bool ignore_case) noexcept {return ends_width(std::basic_string<Char>(str), std::basic_string<Char>(value), ignore_case);}
    /// @endcond

    /// @brief Writes the text representation of the specified arguments list, to string using the specified format information.
    /// @param fmt A composite format string.
    /// @param args anarguments list to write using format.
    /// @return string formated.
    /// @remarks A format specifier follows this prototype:
    /// @remarks %[flags][width][.precision][length]specifier
    /// | specifier | Output                                                                                                                                                   | Example      |
    /// |-----------|----------------------------------------------------------------------------------------------------------------------------------------------------------|--------------|
    /// | d or i    | Signed decimal integer                                                                                                                                   | 392          |
    /// | u         | Unsigned decimal integer                                                                                                                                 | 7235         |
    /// | o         | Unsigned octal                                                                                                                                           | 610          |
    /// | x         | Unsigned hexadecimal integer                                                                                                                             | 7fa          |
    /// | X         | Unsigned hexadecimal integer (uppercase)                                                                                                                 | 7FA          |
    /// | f         | Decimal floating point, lowercase                                                                                                                        | 392.65       |
    /// | F         | Decimal floating point, lowercase (uppercase)                                                                                                            | 392.65       |
    /// | e         | Scientific notation (mantissa/exponent), lowercase                                                                                                       | 3.9265e+2    |
    /// | E         | Scientific notation (mantissa/exponent), uppercase                                                                                                       | 3.9265E+2    |
    /// | g         | Use the shortest representation: %e or %f                                                                                                                | 392.65       |
    /// | G         | Use the shortest representation: %E or %F                                                                                                                | 392.65       |
    /// | a         | Hexadecimal floating point, lowercase                                                                                                                    | -0xc.90fep-2 |
    /// | A         | Hexadecimal floating point, uppercase                                                                                                                    | -0XC.90FEP-2 |
    /// | c         | Character                                                                                                                                                | a            |
    /// | s         | String of characters                                                                                                                                     | sample       |
    /// | p         | Pointer address                                                                                                                                          | b8000000     |
    /// | n         | Nothing printed. The corresponding argument must be a pointer to a signed int. The number of characters written so far is stored in the pointed location |              |
    /// | %         | A % followed by another % character will write a single % to the stream.                                                                                 | %            |
    /// @remarks The format specifier can also contain sub-specifiers: flags, width, .precision and modifiers (in that order), which are optional and follow these specifications:
    /// | flags   | description                                                                                                                                                                                                                                                                                                 |
    /// |---------|-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
    /// | -       | Left-justify within the given field width; Right justification is the default (see width sub-specifier).                                                                                                                                                                                                    |
    /// | +       | Forces to preceed the result with a plus or minus sign (+ or -) even for positive numbers. By default, only negative numbers are preceded with a - sign.                                                                                                                                                    |
    /// | (space) | If no sign is going to be written, a blank space is inserted before the value.                                                                                                                                                                                                                              |
    /// | #       | Used with o, x or X specifiers the value is preceeded with 0, 0x or 0X respectively for values different than zero. Used with a, A, e, E, f, F, g or G it forces the written output to contain a decimal point even if no more digits follow. By default, if no digits follow, no decimal point is written. |
    /// | 0       | Left-pads the number with zeroes (0) instead of spaces when padding is specified (see width sub-specifier).                                                                                                                                                                                                 |
    ///
    /// | width    | description                                                                                                                                                                                          |
    /// |----------|------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
    /// | (number) | Minimum number of characters to be printed. If the value to be printed is shorter than this number, the result is padded with blank spaces. The value is not truncated even if the result is larger. |
    /// | *        | The width is not specified in the format string, but as an additional integer value argument preceding the argument that has to be formatted.                                                        |
    ///
    /// | .precision | description                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              |
    /// |------------|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
    /// | .number    | For integer specifiers (d, i, o, u, x, X): precision specifies the minimum number of digits to be written. If the value to be written is shorter than this number, the result is padded with leading zeros. The value is not truncated even if the result is longer. A precision of 0 means that no character is written for the value 0. For a, A, e, E, f and F specifiers: this is the number of digits to be printed after the decimal point (by default, this is 6). For g and G specifiers: This is the maximum number of significant digits to be printed. For s: this is the maximum number of characters to be printed. By default all characters are printed until the ending null character is encountered. If the period is specified without an explicit value for precision, 0 is assumed. |
    /// | .*         | The precision is not specified in the format string, but as an additional integer value argument preceding the argument that has to be formatted.                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        |
    /// @remarks The length sub-specifier modifies the length of the data type. This is a chart showing the types used to interpret the corresponding arguments with and without length specifier (if a different type is used, the proper type promotion or conversion is performed, if allowed):
    /// | length | d i           | u o x X                | f F e E g G a A | c     | s        | p     | n              |
    /// |--------|---------------|------------------------|-----------------|-------|----------|-------|----------------|
    /// | (none) | int           | unsigned int           | double          | int   | char*    | void* | int*           |
    /// | hh     | signed char   | unsigned char          |                 |       |          |       | unsigned char* |
    /// | h      | short int     | unsigned short int     |                 |       |          |       | short int*     |
    /// | l      | long int      | unsigned long int      |                 | win_t | wchar_t* |       | long int*      |
    /// | ll     | long long int | unsigned long long int |                 |       |          |       | long long int* |
    /// | j      | intmax_t      | uintmax_t              |                 |       |          |       | intmax_t*      |
    /// | z      | size_t        | size_t                 |                 |       |          |       | size_t*        |
    /// | t      | ptrdiff_t     | ptrdiff_t              |                 |       |          |       | ptrdiff_t*     |
    /// | L      |               |                        | long double     |       |          |       |                |
    /// @remarks Note regarding the c specifier: it takes an int (or wint_t) as argument, but performs the proper conversion to a char value (or a wchar_t) before formatting it for output.
    /// @remarks you can use std::string or std::wstring with format param %%s.
    template<typename Char, typename ... Args>
    static std::basic_string<Char> format(const std::basic_string<Char>& fmt, Args&& ... args) noexcept {return __format(fmt.c_str(), convert_param(std::forward<Args>(args)) ...);}

    /// @cond
    template<typename Char, typename ... Args>
    static std::basic_string<Char> format(const Char* fmt, Args&& ... args) noexcept {return __format(fmt, convert_param(std::forward<Args>(args)) ...);}
    /// @endcond
    
    /// @brief Splits a specified string into a maximum number of substrings based on the characters in an array.
    /// @param str string to split.
    /// @param separators A character array that delimits the substrings in this string, an empty array that contains no delimiters.
    /// @param count The maximum number of substrings to return.
    /// @param options xtd::string_split_options::remove_empty_entries to omit empty array elements from the array returned; or None to include empty array elements in the array returned.
    /// @return An array whose elements contain the substrings in this string that are delimited by one or more characters in separators. For more information, see the Remarks section.
    /// @remarks Delimiter characters are not included in the elements of the returned array.
    /// @remarks If this instance does not contain any of the characters in separator, or the count parameter is 1, the returned array consists of a single element that contains this instance.
    /// @remarks If the count parameter is zero, or the options parameter is remove_empty_entries and the length of this instance is zero, an empty array is returned.
    /// @remarks Each element of separator defines a separate delimiter character. If the options parameter is None, and two delimiters are adjacent or a delimiter is found at the beginning or end of this instance, the corresponding array element contains an empty string.
    /// @remarks If there are more than count substrings in this instance, the first count minus 1 substrings are returned in the first count minus 1 elements of the return value, and the remaining characters in this instance are returned in the last element of the return value.
    /// @remarks If count is greater than the number of substrings, the available substrings are returned.
   template<typename Char>
    static std::vector<std::basic_string<Char>> split(const std::basic_string<Char>& str, const std::vector<Char>& separators, size_t count, string_split_options options) noexcept {
      if (count == 0) return {};
      if (count == 1) return {str};
      
      std::vector<std::basic_string<Char>> list;
      std::basic_string<Char> subString;
      std::vector<Char> split_char_separators = separators.size() == 0 ? std::vector<Char> {9, 10, 11, 12, 13, 32} : separators;
      for (std::string::const_iterator it = str.begin(); it != str.end(); it++) {
        bool is_separator =  std::find(split_char_separators.begin(), split_char_separators.end(), *it) != split_char_separators.end();
        if (!is_separator) subString.append(std::string(1, *it));
        if ((it - str.begin() == str.length() - 1 || is_separator) && (subString.length() > 0 || (subString.length() == 0 && options != string_split_options::remove_empty_entries))) {
          if (list.size() == count - 1) {
            list.push_back(subString + std::string(str.c_str(), it - str.begin() + (is_separator ? 1 : 0), str.length() - (it - str.begin()) + (is_separator ? 1 : 0)));
            return list;
          }
          list.push_back(subString);
          subString.clear();
        }
      }
      
      return list;
    }

    /// @brief Splits a specified string into substrings that are based on the default white-space characters. White-space characters are defined by the c++ standard and return true if they are passed to the std::isspace() or std::iswspace() method.
    /// @param str string to split.
    /// @return An array whose elements contain the substrings in this string that are delimited by one or more characters in white-space separators. For more information, see the Remarks section.
    /// @remarks Delimiter characters are not included in the elements of the returned array.
    /// @remarks If this instance does not contain any of the characters in separator, or the count parameter is 1, the returned array consists of a single element that contains this instance.
    template<typename Char>
    static std::vector<std::basic_string<Char>> split(const std::basic_string<Char>& str) noexcept {return split(str, std::vector<Char> {9, 10, 11, 12, 13, 32}, std::numeric_limits<size_t>::max(), string_split_options::none);}
    
    /// @brief Splits a specified string into substrings that are based on the characters in an array.
    /// @param str string to split.
    /// @param separators A character array that delimits the substrings in this string, an empty array that contains no delimiters.
    /// @return An array whose elements contain the substrings in this string that are delimited by one or more characters in separators. For more information, see the Remarks section.
    /// @remarks Delimiter characters are not included in the elements of the returned array.
    /// @remarks If this instance does not contain any of the characters in separator, or the count parameter is 1, the returned array consists of a single element that contains this instance.
    template<typename Char>
    static std::vector<std::basic_string<Char>> split(const std::basic_string<Char>& str, const std::vector<Char>& separators) noexcept {return split(str, separators, std::numeric_limits<size_t>::max(), string_split_options::none);}
    
    /// @brief Splits a specified string into substrings based on the characters in an array. You can specify whether the substrings include empty array elements.
    /// @param str string to split.
    /// @param separators A character array that delimits the substrings in this string, an empty array that contains no delimiters.
    /// @param options xtd::string_split_options::remove_empty_entries to omit empty array elements from the array returned; or None to include empty array elements in the array returned.
    /// @return An array whose elements contain the substrings in this string that are delimited by one or more characters in separators. For more information, see the Remarks section.
    /// @remarks Delimiter characters are not included in the elements of the returned array.
    /// @remarks If this instance does not contain any of the characters in separator, or the count parameter is 1, the returned array consists of a single element that contains this instance.
    /// @remarks If this instance does not contain any of the characters in separator, the returned array consists of a single element that contains this instance.
    /// @remarks If the options parameter is remove_empty_entries and the length of this instance is zero, the method returns an empty array.
    /// @remarks Each element of separator defines a separate delimiter that consists of a single character. If the options argument is none, and two delimiters are adjacent or a delimiter is found at the beginning or end of this instance, the corresponding array element contains empty string. For example, if separator includes two elements, "-" and "_", the value of the string instance is "-_aa-_", and the value of the options argument is None, the method returns a string array with the following five elements:
    ///   1. empty string, which represents the empty string that precedes the "-" character at index 0.
    ///   2. empty string, which represents the empty string between the "-" character at index 0 and the "_" character at index 1.
    ///   3. "aa",
    ///   4. empty string, which represents the empty string that follows the "_" character at index 4.
    ///   5. empty string, which represents the empty string that follows the "-" character at index 5.
    /// @remarks If the separator parameter contains no characters, white-space characters are assumed to be the delimiters. White-space characters are defined by the c++ standard and return true if they are passed to the std::isspace() or std::iswspace() method.
    /// @remarks If count is greater than the number of substrings, the available substrings are returned.
    template<typename Char>
    static std::vector<std::basic_string<Char>> split(const std::basic_string<Char>& str, const std::vector<Char>& separators, string_split_options options) noexcept {return split(str, separators, std::numeric_limits<size_t>::max(), options);}
    
    /// Splits a specified string into a maximum number of substrings based on the characters in an array. You also specify the maximum number of substrings to return.
    /// @param str string to split.
    /// @param separators A character array that delimits the substrings in this string, an empty array that contains no delimiters.
    /// @param count The maximum number of substrings to return.
    /// @remarks Delimiter characters are not included in the elements of the returned array.
    /// @remarks If this instance does not contain any of the characters in separator, or the count parameter is 1, the returned array consists of a single element that contains this instance.
    /// @remarks If the separator parameter contains no characters, white-space characters are assumed to be the delimiters. White-space characters are defined by the Unicode standard and return true if they are passed to the Char.IsWhiteSpace method.
    /// @remarks Each element of separator defines a separate delimiter character. If two delimiters are adjacent, or a delimiter is found at the beginning or end of this instance, the corresponding array element contains empty string.
    /// @remarks If there are more than count substrings in this instance, the first count minus 1 substrings are returned in the first count minus 1 elements of the return value, and the remaining characters in this instance are returned in the last element of the return value.
    template<typename Char>
    static std::vector<std::basic_string<Char>> split(const std::basic_string<Char>& str, const std::vector<Char>& separators, size_t count) noexcept {return split(str, separators, count, string_split_options::none);}

    /// @cond
    template<typename Char>
    static std::vector<std::basic_string<Char>> split(const Char* str, const std::vector<Char>& separators, size_t count, string_split_options options) noexcept {return split(std::basic_string<Char>(str), separators, count, options);}
    template<typename Char>
    static std::vector<std::basic_string<Char>> split(const Char* str) noexcept {return split(str, std::vector<Char> {9, 10, 11, 12, 13, 32}, std::numeric_limits<size_t>::max(), string_split_options::none);}
    template<typename Char>
    static std::vector<std::basic_string<Char>> split(const Char* str, const std::vector<Char>& separators) noexcept {return split(str, separators, std::numeric_limits<size_t>::max(), string_split_options::none);}
    template<typename Char>
    static std::vector<std::basic_string<Char>> split(const Char* str, const std::vector<Char>& separators, string_split_options options) noexcept {return split(str, separators, std::numeric_limits<size_t>::max(), options);}
    template<typename Char>
    static std::vector<std::basic_string<Char>> split(const Char* str, const std::vector<Char>& separators, size_t count) noexcept {return split(str, separators, count, string_split_options::none);}
    /// @endcond

    /// @brief Determines whether the beginning of an instance of String matches a specified String.
    /// @param value A String to compare to.
    /// @return bool true if value matches the beginning of this instance; otherwise, false.
    /// @remarks This method compares value to the substring at the beginning of this instance that is the same length as value, and returns an indication whether they are equal. To be equal, value must be a reference to this same instance, or match the beginning of this instance.
    template<typename Char>
    static bool starts_width(const std::basic_string<Char>& str, const std::basic_string<Char>& value) noexcept {return starts_width(str, value, false);}

    /// @brief Determines whether the beginning of an instance of String matches a specified String, ignoring or honoring their case.
    /// @param value A String to compare to.
    /// @param ignore_case true to ignore case when comparing this instance and value; otherwise, false
    /// @return bool true if value matches the beginning of this instance; otherwise, false.
    /// @remarks This method compares value to the substring at the beginning of this instance that is the same length as value, and returns an indication whether they are equal. To be equal, value must be a reference to this same instance, or match the beginning of this instance.
    template<typename Char>
    static bool starts_width(const std::basic_string<Char>& str, const std::basic_string<Char>& value, bool ignore_case) noexcept {
      if (ignore_case)
        return to_lower(str).find(to_lower(value)) == 0;
      return str.find(value) == 0;
    }

    /// @cond
    template<typename Char>
    static bool starts_width(const std::basic_string<Char>& str, const Char* value) noexcept {return starts_width(str, std::basic_string<Char>(value), false);}
    template<typename Char>
    static bool starts_width(const Char* str, const std::basic_string<Char>& value) noexcept {return starts_width(std::basic_string<Char>(str), value, false);}
    template<typename Char>
    static bool starts_width(const Char* str, const Char* value) noexcept {return starts_width(std::basic_string<Char>(str), std::basic_string<Char>(value), false);}

    template<typename Char>
    static bool starts_width(const std::basic_string<Char>& str, const Char* value, bool ignore_case) noexcept {return starts_width(str, std::basic_string<Char>(value), ignore_case);}
    template<typename Char>
    static bool starts_width(const Char* str, const std::basic_string<Char>& value, bool ignore_case) noexcept {return starts_width(std::basic_string<Char>(str), value, ignore_case);}
    template<typename Char>
    static bool starts_width(const Char* str, const Char* value, bool ignore_case) noexcept {return starts_width(std::basic_string<Char>(str), std::basic_string<Char>(value), ignore_case);}
    /// @endcond
    
    /// @brief Returns a copy of this String converted to lowercase.
    /// @return String A new String in lowercase.
    template<typename Char>
    static const std::basic_string<Char> to_lower(const std::basic_string<Char>& str) noexcept {
      std::basic_string<Char> result;
      std::locale lc = std::locale();
      for(char c : str) result.push_back(std::tolower(c, lc));
      return result;
    }
    
    /// @cond
    static const std::basic_string<char16_t> to_lower(const std::basic_string<char16_t>& str) noexcept {
      std::basic_string<char16_t> result;
      std::locale lc = std::locale();
      //for(char16_t c : str) result.push_back(std::tolower(c, lc));
      for(char16_t c : str) result.push_back(c <= 0xFF ? static_cast<char16_t>(std::tolower(static_cast<char>(c), lc)) : c);
      return result;
    }
    
    static const std::basic_string<char32_t> to_lower(const std::basic_string<char32_t>& str) noexcept {
      std::basic_string<char32_t> result;
      std::locale lc = std::locale();
      //for(char c : str) result.push_back(std::tolower(c, lc));
      for(char32_t c : str) result.push_back(c <= 0xFF ? static_cast<char32_t>(std::tolower(static_cast<char>(c), lc)) : c);
      return result;
    }
    
    template<typename Char>
    static const std::basic_string<Char> to_lower(const Char* str) noexcept {return to_lower(std::basic_string<Char>(str));}
    /// @endcond
    
    /// @brief Returns a copy of this String converted to uppercase.
    /// @return String A new String in uppercase.
    template<typename Char>
    static const std::basic_string<Char> to_upper(const std::basic_string<Char>& str) noexcept {
      std::basic_string<Char> result;
      std::locale lc = std::locale();
      for(char c : str) result.push_back(std::toupper(c, lc));
      return result;
    }
    
    /// @cond
    static const std::basic_string<char16_t> to_upper(const std::basic_string<char16_t>& str) noexcept {
      std::basic_string<char16_t> result;
      std::locale lc = std::locale();
      //for(char16_t c : str) result.push_back(std::toupper(c, lc));
      for(char16_t c : str) result.push_back(c <= 0xFF ? static_cast<char16_t>(std::toupper(static_cast<char>(c), lc)) : c);
      return result;
    }
    
    static const std::basic_string<char32_t> to_upper(const std::basic_string<char32_t>& str) noexcept {
      std::basic_string<char32_t> result;
      std::locale lc = std::locale();
      //for(char c : str) result.push_back(std::toupper(c, lc));
      for(char32_t c : str) result.push_back(c <= 0xFF ? static_cast<char32_t>(std::toupper(static_cast<char>(c), lc)) : c);
      return result;
    }
    
    template<typename Char>
    static const std::basic_string<Char> to_upper(const Char* str) noexcept {return to_upper(std::basic_string<Char>(str));}
    /// @endcond

  private:
    template<typename Arg>
    static auto convert_param(Arg&& arg) noexcept {
      if constexpr (std::is_same<std::remove_cv_t<std::remove_reference_t<Arg>>, std::string>::value) {
        return std::forward<Arg>(arg).c_str();
      } else if constexpr (std::is_same<std::remove_cv_t<std::remove_reference_t<Arg>>, std::wstring>::value) {
        return std::forward<Arg>(arg).c_str();
      }
      else {
        return std::forward<Arg>(arg);
      }
    }
  };
}

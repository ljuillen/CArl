
  const char features[] = {"\n"
"CXX_FEATURE:"
#if __INTEL_COMPILER >= 1600 && ((__cplusplus >= 201300L) || ((__cplusplus == 201103L) && !defined(__INTEL_CXX11_MODE__)) || ((((__INTEL_COMPILER == 1500) && (__INTEL_COMPILER_UPDATE == 1))) && defined(__GXX_EXPERIMENTAL_CXX0X__) && !defined(__INTEL_CXX11_MODE__) ) || (defined(__INTEL_CXX11_MODE__) && defined(__cpp_aggregate_nsdmi)) )
"1"
#else
"0"
#endif
"cxx_aggregate_default_initializers\n"
"CXX_FEATURE:"
#if __INTEL_COMPILER >= 1210 && ((__cplusplus >= 201103L) || defined(__INTEL_CXX11_MODE__) || defined(__GXX_EXPERIMENTAL_CXX0X__))
"1"
#else
"0"
#endif
"cxx_alias_templates\n"
"CXX_FEATURE:"
#if __INTEL_COMPILER >= 1500 && ((__cplusplus >= 201103L) || defined(__INTEL_CXX11_MODE__) || defined(__GXX_EXPERIMENTAL_CXX0X__))
"1"
#else
"0"
#endif
"cxx_alignas\n"
"CXX_FEATURE:"
#if __INTEL_COMPILER >= 1500 && ((__cplusplus >= 201103L) || defined(__INTEL_CXX11_MODE__) || defined(__GXX_EXPERIMENTAL_CXX0X__))
"1"
#else
"0"
#endif
"cxx_alignof\n"
"CXX_FEATURE:"
#if (__cpp_attributes >= 200809 || __INTEL_COMPILER >= 1210) && ((__cplusplus >= 201103L) || defined(__INTEL_CXX11_MODE__) || defined(__GXX_EXPERIMENTAL_CXX0X__))
"1"
#else
"0"
#endif
"cxx_attributes\n"
"CXX_FEATURE:"
#if __INTEL_COMPILER >= 1500 && ((__cplusplus >= 201300L) || ((__cplusplus == 201103L) && !defined(__INTEL_CXX11_MODE__)) || ((((__INTEL_COMPILER == 1500) && (__INTEL_COMPILER_UPDATE == 1))) && defined(__GXX_EXPERIMENTAL_CXX0X__) && !defined(__INTEL_CXX11_MODE__) ) || (defined(__INTEL_CXX11_MODE__) && defined(__cpp_aggregate_nsdmi)) )
"1"
#else
"0"
#endif
"cxx_attribute_deprecated\n"
"CXX_FEATURE:"
#if __INTEL_COMPILER >= 1210 && ((__cplusplus >= 201103L) || defined(__INTEL_CXX11_MODE__) || defined(__GXX_EXPERIMENTAL_CXX0X__))
"1"
#else
"0"
#endif
"cxx_auto_type\n"
"CXX_FEATURE:"
#if __cpp_binary_literals >= 201304 || __INTEL_COMPILER >= 1210
"1"
#else
"0"
#endif
"cxx_binary_literals\n"
"CXX_FEATURE:"
#if __cpp_constexpr >= 200704 || __INTEL_COMPILER >= 1400 && ((__cplusplus >= 201103L) || defined(__INTEL_CXX11_MODE__) || defined(__GXX_EXPERIMENTAL_CXX0X__))
"1"
#else
"0"
#endif
"cxx_constexpr\n"
"CXX_FEATURE:"
#if __INTEL_COMPILER >= 1600 && ((__cplusplus >= 201300L) || ((__cplusplus == 201103L) && !defined(__INTEL_CXX11_MODE__)) || ((((__INTEL_COMPILER == 1500) && (__INTEL_COMPILER_UPDATE == 1))) && defined(__GXX_EXPERIMENTAL_CXX0X__) && !defined(__INTEL_CXX11_MODE__) ) || (defined(__INTEL_CXX11_MODE__) && defined(__cpp_aggregate_nsdmi)) )
"1"
#else
"0"
#endif
"cxx_contextual_conversions\n"
"CXX_FEATURE:"
#if __cpp_decltype >= 200707 || __INTEL_COMPILER >= 1210 && ((__cplusplus >= 201103L) || defined(__INTEL_CXX11_MODE__) || defined(__GXX_EXPERIMENTAL_CXX0X__))
"1"
#else
"0"
#endif
"cxx_decltype\n"
"CXX_FEATURE:"
#if __cpp_decltype_auto >= 201304 || __INTEL_COMPILER >= 1500 && ((__cplusplus >= 201300L) || ((__cplusplus == 201103L) && !defined(__INTEL_CXX11_MODE__)) || ((((__INTEL_COMPILER == 1500) && (__INTEL_COMPILER_UPDATE == 1))) && defined(__GXX_EXPERIMENTAL_CXX0X__) && !defined(__INTEL_CXX11_MODE__) ) || (defined(__INTEL_CXX11_MODE__) && defined(__cpp_aggregate_nsdmi)) )
"1"
#else
"0"
#endif
"cxx_decltype_auto\n"
"CXX_FEATURE:"
#if ((__cplusplus >= 201103L) || defined(__INTEL_CXX11_MODE__) || defined(__GXX_EXPERIMENTAL_CXX0X__)) && (__INTEL_COMPILER > 1400 || (__INTEL_COMPILER == 1400 && __INTEL_COMPILER_UPDATE >= 2)) && !defined(_MSC_VER)
"1"
#else
"0"
#endif
"cxx_decltype_incomplete_return_types\n"
"CXX_FEATURE:"
#if __INTEL_COMPILER >= 1210 && ((__cplusplus >= 201103L) || defined(__INTEL_CXX11_MODE__) || defined(__GXX_EXPERIMENTAL_CXX0X__))
"1"
#else
"0"
#endif
"cxx_default_function_template_args\n"
"CXX_FEATURE:"
#if __INTEL_COMPILER >= 1210 && ((__cplusplus >= 201103L) || defined(__INTEL_CXX11_MODE__) || defined(__GXX_EXPERIMENTAL_CXX0X__))
"1"
#else
"0"
#endif
"cxx_defaulted_functions\n"
"CXX_FEATURE:"
#if __INTEL_COMPILER >= 1400 && ((__cplusplus >= 201103L) || defined(__INTEL_CXX11_MODE__) || defined(__GXX_EXPERIMENTAL_CXX0X__))
"1"
#else
"0"
#endif
"cxx_defaulted_move_initializers\n"
"CXX_FEATURE:"
#if __INTEL_COMPILER >= 1400 && ((__cplusplus >= 201103L) || defined(__INTEL_CXX11_MODE__) || defined(__GXX_EXPERIMENTAL_CXX0X__))
"1"
#else
"0"
#endif
"cxx_delegating_constructors\n"
"CXX_FEATURE:"
#if __INTEL_COMPILER >= 1210 && ((__cplusplus >= 201103L) || defined(__INTEL_CXX11_MODE__) || defined(__GXX_EXPERIMENTAL_CXX0X__))
"1"
#else
"0"
#endif
"cxx_deleted_functions\n"
"CXX_FEATURE:"
#if __INTEL_COMPILER >= 1600 && ((__cplusplus >= 201300L) || ((__cplusplus == 201103L) && !defined(__INTEL_CXX11_MODE__)) || ((((__INTEL_COMPILER == 1500) && (__INTEL_COMPILER_UPDATE == 1))) && defined(__GXX_EXPERIMENTAL_CXX0X__) && !defined(__INTEL_CXX11_MODE__) ) || (defined(__INTEL_CXX11_MODE__) && defined(__cpp_aggregate_nsdmi)) )
"1"
#else
"0"
#endif
"cxx_digit_separators\n"
"CXX_FEATURE:"
#if __INTEL_COMPILER >= 1400 && ((__cplusplus >= 201103L) || defined(__INTEL_CXX11_MODE__) || defined(__GXX_EXPERIMENTAL_CXX0X__))
"1"
#else
"0"
#endif
"cxx_enum_forward_declarations\n"
"CXX_FEATURE:"
#if __INTEL_COMPILER >= 1300 && ((__cplusplus >= 201103L) || defined(__INTEL_CXX11_MODE__) || defined(__GXX_EXPERIMENTAL_CXX0X__))
"1"
#else
"0"
#endif
"cxx_explicit_conversions\n"
"CXX_FEATURE:"
#if __INTEL_COMPILER >= 1210 && ((__cplusplus >= 201103L) || defined(__INTEL_CXX11_MODE__) || defined(__GXX_EXPERIMENTAL_CXX0X__))
"1"
#else
"0"
#endif
"cxx_extended_friend_declarations\n"
"CXX_FEATURE:"
#if __INTEL_COMPILER >= 1210 && ((__cplusplus >= 201103L) || defined(__INTEL_CXX11_MODE__) || defined(__GXX_EXPERIMENTAL_CXX0X__))
"1"
#else
"0"
#endif
"cxx_extern_templates\n"
"CXX_FEATURE:"
#if __INTEL_COMPILER >= 1400 && ((__cplusplus >= 201103L) || defined(__INTEL_CXX11_MODE__) || defined(__GXX_EXPERIMENTAL_CXX0X__))
"1"
#else
"0"
#endif
"cxx_final\n"
"CXX_FEATURE:"
#if __INTEL_COMPILER >= 1210 && ((__cplusplus >= 201103L) || defined(__INTEL_CXX11_MODE__) || defined(__GXX_EXPERIMENTAL_CXX0X__))
"1"
#else
"0"
#endif
"cxx_func_identifier\n"
"CXX_FEATURE:"
#if __INTEL_COMPILER >= 1400 && ((__cplusplus >= 201103L) || defined(__INTEL_CXX11_MODE__) || defined(__GXX_EXPERIMENTAL_CXX0X__))
"1"
#else
"0"
#endif
"cxx_generalized_initializers\n"
"CXX_FEATURE:"
#if __cpp_generic_lambdas >= 201304
"1"
#else
"0"
#endif
"cxx_generic_lambdas\n"
"CXX_FEATURE:"
#if __INTEL_COMPILER >= 1500 && ((__cplusplus >= 201103L) || defined(__INTEL_CXX11_MODE__) || defined(__GXX_EXPERIMENTAL_CXX0X__))
"1"
#else
"0"
#endif
"cxx_inheriting_constructors\n"
"CXX_FEATURE:"
#if __INTEL_COMPILER >= 1400 && ((__cplusplus >= 201103L) || defined(__INTEL_CXX11_MODE__) || defined(__GXX_EXPERIMENTAL_CXX0X__))
"1"
#else
"0"
#endif
"cxx_inline_namespaces\n"
"CXX_FEATURE:"
#if (__cpp_lambdas >= 200907 || __INTEL_COMPILER >= 1210) && ((__cplusplus >= 201103L) || defined(__INTEL_CXX11_MODE__) || defined(__GXX_EXPERIMENTAL_CXX0X__))
"1"
#else
"0"
#endif
"cxx_lambdas\n"
"CXX_FEATURE:"
#if (__cpp_init_captures >= 201304 || __INTEL_COMPILER >= 1500) && ((__cplusplus >= 201300L) || ((__cplusplus == 201103L) && !defined(__INTEL_CXX11_MODE__)) || ((((__INTEL_COMPILER == 1500) && (__INTEL_COMPILER_UPDATE == 1))) && defined(__GXX_EXPERIMENTAL_CXX0X__) && !defined(__INTEL_CXX11_MODE__) ) || (defined(__INTEL_CXX11_MODE__) && defined(__cpp_aggregate_nsdmi)) )
"1"
#else
"0"
#endif
"cxx_lambda_init_captures\n"
"CXX_FEATURE:"
#if __INTEL_COMPILER >= 1210 && ((__cplusplus >= 201103L) || defined(__INTEL_CXX11_MODE__) || defined(__GXX_EXPERIMENTAL_CXX0X__))
"1"
#else
"0"
#endif
"cxx_local_type_template_args\n"
"CXX_FEATURE:"
#if __INTEL_COMPILER >= 1210 && ((__cplusplus >= 201103L) || defined(__INTEL_CXX11_MODE__) || defined(__GXX_EXPERIMENTAL_CXX0X__))
"1"
#else
"0"
#endif
"cxx_long_long_type\n"
"CXX_FEATURE:"
#if __INTEL_COMPILER >= 1400 && ((__cplusplus >= 201103L) || defined(__INTEL_CXX11_MODE__) || defined(__GXX_EXPERIMENTAL_CXX0X__))
"1"
#else
"0"
#endif
"cxx_noexcept\n"
"CXX_FEATURE:"
#if __INTEL_COMPILER >= 1400 && ((__cplusplus >= 201103L) || defined(__INTEL_CXX11_MODE__) || defined(__GXX_EXPERIMENTAL_CXX0X__))
"1"
#else
"0"
#endif
"cxx_nonstatic_member_init\n"
"CXX_FEATURE:"
#if __INTEL_COMPILER >= 1210 && ((__cplusplus >= 201103L) || defined(__INTEL_CXX11_MODE__) || defined(__GXX_EXPERIMENTAL_CXX0X__))
"1"
#else
"0"
#endif
"cxx_nullptr\n"
"CXX_FEATURE:"
#if __INTEL_COMPILER >= 1400 && ((__cplusplus >= 201103L) || defined(__INTEL_CXX11_MODE__) || defined(__GXX_EXPERIMENTAL_CXX0X__))
"1"
#else
"0"
#endif
"cxx_override\n"
"CXX_FEATURE:"
#if __INTEL_COMPILER >= 1300 && ((__cplusplus >= 201103L) || defined(__INTEL_CXX11_MODE__) || defined(__GXX_EXPERIMENTAL_CXX0X__))
"1"
#else
"0"
#endif
"cxx_range_for\n"
"CXX_FEATURE:"
#if __cpp_raw_strings >= 200710 || __INTEL_COMPILER >= 1400 && ((__cplusplus >= 201103L) || defined(__INTEL_CXX11_MODE__) || defined(__GXX_EXPERIMENTAL_CXX0X__))
"1"
#else
"0"
#endif
"cxx_raw_string_literals\n"
"CXX_FEATURE:"
#if __INTEL_COMPILER >= 1400 && ((__cplusplus >= 201103L) || defined(__INTEL_CXX11_MODE__) || defined(__GXX_EXPERIMENTAL_CXX0X__))
"1"
#else
"0"
#endif
"cxx_reference_qualified_functions\n"
"CXX_FEATURE:"
#if __cpp_constexpr >= 201304 || (__INTEL_COMPILER >= 1700 && ((__cplusplus >= 201300L) || ((__cplusplus == 201103L) && !defined(__INTEL_CXX11_MODE__)) || ((((__INTEL_COMPILER == 1500) && (__INTEL_COMPILER_UPDATE == 1))) && defined(__GXX_EXPERIMENTAL_CXX0X__) && !defined(__INTEL_CXX11_MODE__) ) || (defined(__INTEL_CXX11_MODE__) && defined(__cpp_aggregate_nsdmi)) ) && __INTEL_COMPILER != 1800 && !defined(_MSC_VER))
"1"
#else
"0"
#endif
"cxx_relaxed_constexpr\n"
"CXX_FEATURE:"
#if __cpp_return_type_deduction >= 201304 || __INTEL_COMPILER >= 1500 && ((__cplusplus >= 201300L) || ((__cplusplus == 201103L) && !defined(__INTEL_CXX11_MODE__)) || ((((__INTEL_COMPILER == 1500) && (__INTEL_COMPILER_UPDATE == 1))) && defined(__GXX_EXPERIMENTAL_CXX0X__) && !defined(__INTEL_CXX11_MODE__) ) || (defined(__INTEL_CXX11_MODE__) && defined(__cpp_aggregate_nsdmi)) )
"1"
#else
"0"
#endif
"cxx_return_type_deduction\n"
"CXX_FEATURE:"
#if __INTEL_COMPILER >= 1210 && ((__cplusplus >= 201103L) || defined(__INTEL_CXX11_MODE__) || defined(__GXX_EXPERIMENTAL_CXX0X__))
"1"
#else
"0"
#endif
"cxx_right_angle_brackets\n"
"CXX_FEATURE:"
#if (__cpp_rvalue_references >= 200610 || __INTEL_COMPILER >= 1210) && ((__cplusplus >= 201103L) || defined(__INTEL_CXX11_MODE__) || defined(__GXX_EXPERIMENTAL_CXX0X__))
"1"
#else
"0"
#endif
"cxx_rvalue_references\n"
"CXX_FEATURE:"
#if __INTEL_COMPILER >= 1400 && ((__cplusplus >= 201103L) || defined(__INTEL_CXX11_MODE__) || defined(__GXX_EXPERIMENTAL_CXX0X__))
"1"
#else
"0"
#endif
"cxx_sizeof_member\n"
"CXX_FEATURE:"
#if (__cpp_static_assert >= 200410 || __INTEL_COMPILER >= 1210) && ((__cplusplus >= 201103L) || defined(__INTEL_CXX11_MODE__) || defined(__GXX_EXPERIMENTAL_CXX0X__))
"1"
#else
"0"
#endif
"cxx_static_assert\n"
"CXX_FEATURE:"
#if __INTEL_COMPILER >= 1400 && ((__cplusplus >= 201103L) || defined(__INTEL_CXX11_MODE__) || defined(__GXX_EXPERIMENTAL_CXX0X__))
"1"
#else
"0"
#endif
"cxx_strong_enums\n"
"CXX_FEATURE:"
#if __INTEL_COMPILER >= 1210 && ((__cplusplus >= 201103L) || defined(__INTEL_CXX11_MODE__) || defined(__GXX_EXPERIMENTAL_CXX0X__))
"1"
#else
"0"
#endif
"cxx_template_template_parameters\n"
"CXX_FEATURE:"
#if __INTEL_COMPILER >= 1500 && ((__cplusplus >= 201103L) || defined(__INTEL_CXX11_MODE__) || defined(__GXX_EXPERIMENTAL_CXX0X__))
"1"
#else
"0"
#endif
"cxx_thread_local\n"
"CXX_FEATURE:"
#if __INTEL_COMPILER >= 1210 && ((__cplusplus >= 201103L) || defined(__INTEL_CXX11_MODE__) || defined(__GXX_EXPERIMENTAL_CXX0X__))
"1"
#else
"0"
#endif
"cxx_trailing_return_types\n"
"CXX_FEATURE:"
#if __cpp_unicode_literals >= 200710 || (__INTEL_COMPILER >= 1400 && ((__cplusplus >= 201103L) || defined(__INTEL_CXX11_MODE__) || defined(__GXX_EXPERIMENTAL_CXX0X__)) && (!defined(_MSC_VER) || __INTEL_COMPILER >= 1600))
"1"
#else
"0"
#endif
"cxx_unicode_literals\n"
"CXX_FEATURE:"
#if __INTEL_COMPILER >= 1300 && ((__cplusplus >= 201103L) || defined(__INTEL_CXX11_MODE__) || defined(__GXX_EXPERIMENTAL_CXX0X__))
"1"
#else
"0"
#endif
"cxx_uniform_initialization\n"
"CXX_FEATURE:"
#if __INTEL_COMPILER >= 1400 && ((__cplusplus >= 201103L) || defined(__INTEL_CXX11_MODE__) || defined(__GXX_EXPERIMENTAL_CXX0X__))
"1"
#else
"0"
#endif
"cxx_unrestricted_unions\n"
"CXX_FEATURE:"
#if __cpp_user_defined_literals >= 200809 || (__INTEL_COMPILER >= 1500 && ((__cplusplus >= 201103L) || defined(__INTEL_CXX11_MODE__) || defined(__GXX_EXPERIMENTAL_CXX0X__)) && (!defined(_MSC_VER) || __INTEL_COMPILER >= 1600))
"1"
#else
"0"
#endif
"cxx_user_literals\n"
"CXX_FEATURE:"
#if __cpp_variable_templates >= 201304
"1"
#else
"0"
#endif
"cxx_variable_templates\n"
"CXX_FEATURE:"
#if __INTEL_COMPILER >= 1210 && ((__cplusplus >= 201103L) || defined(__INTEL_CXX11_MODE__) || defined(__GXX_EXPERIMENTAL_CXX0X__))
"1"
#else
"0"
#endif
"cxx_variadic_macros\n"
"CXX_FEATURE:"
#if (__cpp_variadic_templates >= 200704 || __INTEL_COMPILER >= 1210) && ((__cplusplus >= 201103L) || defined(__INTEL_CXX11_MODE__) || defined(__GXX_EXPERIMENTAL_CXX0X__))
"1"
#else
"0"
#endif
"cxx_variadic_templates\n"

};

int main(int argc, char** argv) { (void)argv; return features[argc]; }

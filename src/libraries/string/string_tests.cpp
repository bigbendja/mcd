#include <iostream>
#include <cassert>
#include "string.h"

void testBasicOperations() {
    // Concatenate
    assert((BasicOperations::concatenate("Hello", " World") == "Hello World") && "Error in BasicOperations::concatenate");

    // Substring
    assert((BasicOperations::substring("MC++ Language", 0, 4) == "MC++") && "Error in BasicOperations::substring");

    // IndexOf
    assert((BasicOperations::indexOf("Testing MC++ Library", "MC++") == 8) && "Error in BasicOperations::indexOf");

    // Replace
    assert((BasicOperations::replace("Hello World", "World", "MC++") == "Hello MC++") && "Error in BasicOperations::replace");

    // Split
    auto words = BasicOperations::split("one,two,three", ",");
    assert((words.size() == 3 && words[0] == "one" && words[1] == "two" && words[2] == "three") && "Error in BasicOperations::split");

    // Reverse
    assert((BasicOperations::reverse("MC++") == "++CM") && "Error in BasicOperations::reverse");
}

void testTextTransformation() {
    // To Upper
    assert((TextTransformation::toUpper("mc++") == "MC++") && "Error in TextTransformation::toUpper");

    // To Lower
    assert((TextTransformation::toLower("MC++") == "mc++") && "Error in TextTransformation::toLower");

    // Capitalize
    assert((TextTransformation::capitalize("language") == "Language") && "Error in TextTransformation::capitalize");

    // Trim
    assert((TextTransformation::trim("   trimmed text   ") == "trimmed text") && "Error in TextTransformation::trim");

    // Remove Whitespace
    assert((TextTransformation::removeWhitespace("M C + +") == "MC++") && "Error in TextTransformation::removeWhitespace");

    // Replace Char
    assert((TextTransformation::replaceChar("MC--", '-', '+') == "MC++") && "Error in TextTransformation::replaceChar");

    // To Title Case
    assert((TextTransformation::toTitleCase("mc++ programming language") == "Mc++ Programming Language") && "Error in TextTransformation::toTitleCase");

    // To Snake Case
    assert((TextTransformation::toSnakeCase("Snake Case Example") == "snake_case_example") && "Error in TextTransformation::toSnakeCase");

    // To Kebab Case
    assert((TextTransformation::toKebabCase("Kebab Case Example") == "kebab-case-example") && "Error in TextTransformation::toKebabCase");
}

void testAnalysisAdvanced() {
    // Length
    assert((AnalysisAdvanced::length("MC++") == 4) && "Error in AnalysisAdvanced::length");

    // Count Occurrences
    assert((AnalysisAdvanced::countOccurrences("MC++ MC++ MC++", "MC++") == 3) && "Error in AnalysisAdvanced::countOccurrences");

    // Is Empty
    assert((AnalysisAdvanced::isEmpty("") == true) && "Error in AnalysisAdvanced::isEmpty (empty case)");
    assert((AnalysisAdvanced::isEmpty("not empty") == false) && "Error in AnalysisAdvanced::isEmpty (non-empty case)");

    // Starts With
    assert((AnalysisAdvanced::startsWith("MC++ Language", "MC++") == true) && "Error in AnalysisAdvanced::startsWith");

    // Ends With
    assert((AnalysisAdvanced::endsWith("MC++ Language", "Language") == true) && "Error in AnalysisAdvanced::endsWith");

    // Contains Only Alpha
    assert((AnalysisAdvanced::containsOnlyAlpha("MCplusplus") == true) && "Error in AnalysisAdvanced::containsOnlyAlpha (alpha case)");
    assert((AnalysisAdvanced::containsOnlyAlpha("MC++123") == false) && "Error in AnalysisAdvanced::containsOnlyAlpha (non-alpha case)");

    // Contains Only Digits
    assert((AnalysisAdvanced::containsOnlyDigits("123456") == true) && "Error in AnalysisAdvanced::containsOnlyDigits (digits case)");
    assert((AnalysisAdvanced::containsOnlyDigits("MC++") == false) && "Error in AnalysisAdvanced::containsOnlyDigits (non-digits case)");

    // Word Count
    assert((AnalysisAdvanced::wordCount("MC++ is great") == 3) && "Error in AnalysisAdvanced::wordCount");

    // Char Frequency
    auto freq = AnalysisAdvanced::charFrequency("MC++");
    assert((freq['M'] == 1 && freq['C'] == 1 && freq['+'] == 2) && "Error in AnalysisAdvan                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  
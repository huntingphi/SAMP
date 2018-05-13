#include "../include/catch.hpp"
#include "../include/Audio.h"
#include <string>
#include <vector>
TEST_CASE("Test constructor"){
        int sample_rate = 44100;
        std::vector<int8_t> sample_array_8_1 = {1,2,3,4,5,1,2,3,4,5};
        std::vector<int16_t> sample_array_16_1 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
        std::vector<std::pair<int8_t, int8_t>> sample_array_8_2 = {std::make_pair(1, 1), std::make_pair(2, 2), std::make_pair(3, 3), std::make_pair(4, 4), std::make_pair(5, 5), std::make_pair(6, 6), std::make_pair(7, 7), std::make_pair(8, 8), std::make_pair(9, 9), std::make_pair(10, 10)};
        std::vector<std::pair<int16_t, int16_t>> sample_array_16_2 = {std::make_pair(1, 1), std::make_pair(2, 2), std::make_pair(3, 3), std::make_pair(4, 4), std::make_pair(5, 5), std::make_pair(6, 6), std::make_pair(7, 7), std::make_pair(8, 8), std::make_pair(9, 9), std::make_pair(10, 10)};

        Audio<int8_t> a_8_1(sample_array_8_1,sample_rate);
        Audio<std::pair<int8_t, int8_t>> a_8_2(sample_array_8_2, sample_rate);
        Audio<int16_t> a_16_1(sample_array_16_1,sample_rate);
        Audio<std::pair<int16_t, int16_t>> a_16_2(sample_array_16_2, sample_rate);
        // a_8_1()
        std::string a_8_1_expected = "N: 1 Bit depth: 8 Samples: 10 Sample rate: 44100";
        std::string a_8_1_resulting = a_8_1.toString();
        std::string a_8_2_expected = "N: 2 Bit depth: 8 Samples: 10 Sample rate: 44100";
        std::string a_8_2_resulting = a_8_2.toString();
        std::string a_16_1_expected = "N: 1 Bit depth: 16 Samples: 10 Sample rate: 44100";
        std::string a_16_1_resulting = a_16_1.toString();
        std::string a_16_2_expected = "N: 2 Bit depth: 16 Samples: 10 Sample rate: 44100";
        std::string a_16_2_resulting = a_16_2.toString();
        REQUIRE(a_8_1_expected == a_8_1_resulting);
        REQUIRE(a_8_2_expected == a_8_2_resulting);
        REQUIRE(a_16_1_expected == a_16_1_resulting);
        REQUIRE(a_16_2_expected == a_16_2_resulting);
}
TEST_CASE("Test destructor"){
        REQUIRE(1==0);
}


TEST_CASE("Test copy constructor"){
        REQUIRE(1==0);
}


TEST_CASE("Test copy assignment"){
        REQUIRE(1==0);
}


TEST_CASE("Test move constructor"){
        REQUIRE(1==0);
}


TEST_CASE("Test move assignment"){
        REQUIRE(1==0);
}

TEST_CASE("Test iterator begin"){


        REQUIRE(1==0);
}


TEST_CASE("Test iterator end"){
        REQUIRE(1==0);
}


TEST_CASE("Test iterator++"){
        REQUIRE(1==0);
}

TEST_CASE("Test iterator--"){
        REQUIRE(1==0);
}

TEST_CASE("Test reverse"){
        REQUIRE(1==0);
}

TEST_CASE("Test compute rms"){
        REQUIRE(1==0);
}

TEST_CASE("Test cut"){
        REQUIRE(1==0);
}

TEST_CASE("Test ranged add"){
        REQUIRE(1==0);
}

TEST_CASE("Test concatinate"){
        REQUIRE(1==0);
}

TEST_CASE("Test volume factor"){
        REQUIRE(1==0);
}


TEST_CASE("Test normalisation"){
        REQUIRE(1==0);
}

TEST_CASE("Test fade in"){
        REQUIRE(1==0);
}

TEST_CASE("Test fade out"){
        REQUIRE(1==0);
}

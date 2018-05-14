#include "../include/catch.hpp"
#include "../include/Audio.h"
#include <string>
#include <vector>
int sample_rate = 44100;
std::vector<int8_t> sample_array_8_1 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
std::vector<int16_t> sample_array_16_1 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
std::vector<std::pair<int8_t, int8_t>> sample_array_8_2 = {std::make_pair(1, 1), std::make_pair(2, 2), std::make_pair(3, 3), std::make_pair(4, 4), std::make_pair(5, 5), std::make_pair(6, 6), std::make_pair(7, 7), std::make_pair(8, 8), std::make_pair(9, 9), std::make_pair(10, 10)};
std::vector<std::pair<int16_t, int16_t>> sample_array_16_2 = {std::make_pair(1, 1), std::make_pair(2, 2), std::make_pair(3, 3), std::make_pair(4, 4), std::make_pair(5, 5), std::make_pair(6, 6), std::make_pair(7, 7), std::make_pair(8, 8), std::make_pair(9, 9), std::make_pair(10, 10)};

Audio<int8_t> mono8bit(sample_array_8_1, sample_rate);
Audio<std::pair<int8_t, int8_t>> stereo8bit(sample_array_8_2, sample_rate);
Audio<int16_t> mono16bit(sample_array_16_1, sample_rate);
Audio<std::pair<int16_t, int16_t>> stereo16bit(sample_array_16_2, sample_rate);
TEST_CASE("Test constructor"){
        // mono8bit()
        std::string a_8_1_expected = "N: 1 Bit depth: 8 Samples: 10 Sample rate: 44100";
        std::string a_8_1_resulting = mono8bit.toString();
        std::string a_8_2_expected = "N: 2 Bit depth: 8 Samples: 10 Sample rate: 44100";
        std::string a_8_2_resulting = stereo8bit.toString();
        std::string a_16_1_expected = "N: 1 Bit depth: 16 Samples: 10 Sample rate: 44100";
        std::string a_16_1_resulting = mono16bit.toString();
        std::string a_16_2_expected = "N: 2 Bit depth: 16 Samples: 10 Sample rate: 44100";
        std::string a_16_2_resulting = stereo16bit.toString();
        REQUIRE(a_8_1_expected == a_8_1_resulting);
        REQUIRE(a_8_2_expected == a_8_2_resulting);
        REQUIRE(a_16_1_expected == a_16_1_resulting);
        REQUIRE(a_16_2_expected == a_16_2_resulting);
}
TEST_CASE("Test destructor"){
        REQUIRE(1==0);
}


TEST_CASE("Test copy constructor"){
        Audio<int8_t> mono8bit_result(mono8bit);
        Audio<int16_t> mono16bit_result(mono16bit);
        Audio<std::pair<int8_t,int8_t>> stereo8bit_result(stereo8bit);
        Audio<std::pair<int16_t, int16_t>> stereo16bit_result(stereo16bit);
        //Overloaded == operator to test for equality
        REQUIRE(mono8bit==mono8bit_result);
        REQUIRE(mono16bit == mono16bit_result);
        REQUIRE(stereo8bit == stereo8bit_result);
        REQUIRE(stereo16bit == stereo16bit_result);
}


TEST_CASE("Test copy assignment"){
        Audio<int8_t> mono8bit_result;
        Audio<int16_t> mono16bit_result;
        Audio<std::pair<int8_t, int8_t>> stereo8bit_result;
        Audio<std::pair<int16_t, int16_t>> stereo16bit_result;
        mono8bit_result = mono8bit;
        mono16bit_result = mono16bit;
        stereo8bit_result = stereo8bit;
        stereo16bit_result = stereo16bit;

        //Overloaded == operator to test for equality
        REQUIRE(mono8bit == mono8bit_result);
        REQUIRE(mono16bit == mono16bit_result);
        REQUIRE(stereo8bit == stereo8bit_result);
        REQUIRE(stereo16bit == stereo16bit_result);
}


TEST_CASE("Test move constructor"){

        Audio<int8_t> mono8bit_to_move(sample_array_8_1, sample_rate);
        Audio<std::pair<int8_t, int8_t>> stereo8bit_to_move(sample_array_8_2, sample_rate);
        Audio<int16_t> mono16bit_to_move(sample_array_16_1, sample_rate);
        Audio<std::pair<int16_t, int16_t>> stereo16bit_to_move(sample_array_16_2, sample_rate);

        Audio<int8_t> mono8bit_result(std::move(mono8bit_to_move));
        Audio<int16_t> mono16bit_result(std::move(mono16bit_to_move));
        Audio<std::pair<int8_t, int8_t>> stereo8bit_result(std::move(stereo8bit_to_move));
        Audio<std::pair<int16_t, int16_t>> stereo16bit_result(std::move(stereo16bit_to_move));

        REQUIRE_FALSE(mono8bit_to_move == mono8bit_result);
        REQUIRE_FALSE(mono16bit_to_move == mono16bit_result);
        REQUIRE_FALSE(stereo8bit_to_move == stereo8bit_result);
        REQUIRE_FALSE(stereo16bit_to_move == stereo16bit_result);

        REQUIRE(mono8bit == mono8bit_result);
        REQUIRE(mono16bit == mono16bit_result);
        REQUIRE(stereo8bit == stereo8bit_result);
        REQUIRE(stereo16bit == stereo16bit_result);
}


TEST_CASE("Test move assignment"){
        Audio<int8_t> mono8bit_to_move(sample_array_8_1, sample_rate);
        Audio<std::pair<int8_t, int8_t>> stereo8bit_to_move(sample_array_8_2, sample_rate);
        Audio<int16_t> mono16bit_to_move(sample_array_16_1, sample_rate);
        Audio<std::pair<int16_t, int16_t>> stereo16bit_to_move(sample_array_16_2, sample_rate);

        Audio<int8_t> mono8bit_result;
        Audio<int16_t> mono16bit_result;
        Audio<std::pair<int8_t, int8_t>> stereo8bit_result;
        Audio<std::pair<int16_t, int16_t>> stereo16bit_result;
        mono8bit_result = std::move(mono8bit_to_move);
        mono16bit_result = std::move(mono16bit_to_move);
        stereo8bit_result = std::move(stereo8bit_to_move);
        stereo16bit_result = std::move(stereo16bit_to_move);

        REQUIRE_FALSE(mono8bit_to_move == mono8bit_result);
        REQUIRE_FALSE(mono16bit_to_move == mono16bit_result);
        REQUIRE_FALSE(stereo8bit_to_move == stereo8bit_result);
        REQUIRE_FALSE(stereo16bit_to_move == stereo16bit_result);

        REQUIRE(mono8bit == mono8bit_result);
        REQUIRE(mono16bit == mono16bit_result);
        REQUIRE(stereo8bit == stereo8bit_result);
        REQUIRE(stereo16bit == stereo16bit_result);
}

// TEST_CASE("Test iterator begin"){


//         REQUIRE(1==0);
// }


// TEST_CASE("Test iterator end"){
//         REQUIRE(1==0);
// }


// TEST_CASE("Test iterator++"){
//         REQUIRE(1==0);
// }

// TEST_CASE("Test iterator--"){
//         REQUIRE(1==0);
// }

TEST_CASE("Test reverse"){
        std::vector<int8_t> sample_array_8_1_reversed = {5, 4, 3, 2, 1, 5, 4, 3, 2, 1};
        std::vector<int16_t> sample_array_16_1_reversed = {5, 4, 3, 2, 1, 5, 4, 3, 2, 1};;
        std::vector<std::pair<int8_t, int8_t>> sample_array_8_2_reversed =
            {
                std::make_pair(10, 10),
                std::make_pair(9, 9),
                std::make_pair(8, 8),
                std::make_pair(7, 7),
                std::make_pair(6, 6),
                std::make_pair(5, 5),
                std::make_pair(4, 4),
                std::make_pair(3, 3),
                std::make_pair(2, 2),
                std::make_pair(1, 1)
                };
        std::vector<std::pair<int16_t, int16_t>> sample_array_16_2_reversed =
            {
                std::make_pair(10, 10),
                std::make_pair(9, 9),
                std::make_pair(8, 8),
                std::make_pair(7, 7),
                std::make_pair(6, 6),
                std::make_pair(5, 5),
                std::make_pair(4, 4),
                std::make_pair(3, 3),
                std::make_pair(2, 2),
                std::make_pair(1, 1)
                };
        Audio<int8_t> mono8bit_reversed(sample_array_8_1_reversed, sample_rate);
        Audio<std::pair<int8_t, int8_t>> stereo8bit_reversed(sample_array_8_2_reversed, sample_rate);
        Audio<int16_t> mono16bit_reversed(sample_array_16_1_reversed, sample_rate);
        Audio<std::pair<int16_t, int16_t>> stereo16bit_reversed(sample_array_16_2_reversed, sample_rate);

        Audio<int8_t> mono8bit_result(mono8bit);
        Audio<int16_t> mono16bit_result(mono16bit);
        Audio<std::pair<int8_t, int8_t>> stereo8bit_result(stereo8bit);
        Audio<std::pair<int16_t, int16_t>> stereo16bit_result(stereo16bit);
        mono8bit_result.reverse();
        mono16bit_result.reverse();
        stereo8bit_result.reverse();
        stereo16bit_result.reverse();

        REQUIRE(mono8bit_result == mono8bit_reversed);
        REQUIRE(mono16bit_result == mono16bit_reversed);
        REQUIRE(stereo8bit_result == stereo8bit_reversed);
        REQUIRE(stereo16bit_result == stereo16bit_reversed);
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

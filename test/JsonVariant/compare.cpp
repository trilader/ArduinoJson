// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2018
// MIT License

#include <ArduinoJson.h>
#include <catch.hpp>

static const char* null = 0;

template <typename T>
void checkEquals(T a, T b) {
  DynamicJsonDocument doc;
  JsonVariant variant = doc.to<JsonVariant>();
  variant.set(a);

  REQUIRE(b == variant);
  REQUIRE(variant == b);
  REQUIRE(b <= variant);
  REQUIRE(variant <= b);
  REQUIRE(b >= variant);
  REQUIRE(variant >= b);

  REQUIRE_FALSE(b != variant);
  REQUIRE_FALSE(variant != b);
  REQUIRE_FALSE(b > variant);
  REQUIRE_FALSE(variant > b);
  REQUIRE_FALSE(b < variant);
  REQUIRE_FALSE(variant < b);
}

template <typename T>
void checkGreater(T a, T b) {
  DynamicJsonDocument doc;
  JsonVariant variant = doc.to<JsonVariant>();
  variant.set(a);

  REQUIRE(variant > b);
  REQUIRE(b < variant);
  REQUIRE(variant != b);
  REQUIRE(b != variant);

  REQUIRE_FALSE(variant < b);
  REQUIRE_FALSE(b > variant);
  REQUIRE_FALSE(variant == b);
  REQUIRE_FALSE(b == variant);
}

template <typename T>
void checkLower(T a, T b) {
  DynamicJsonDocument doc;
  JsonVariant variant = doc.to<JsonVariant>();
  variant.set(a);

  REQUIRE(variant < b);
  REQUIRE(b > variant);
  REQUIRE(variant != b);
  REQUIRE(b != variant);

  REQUIRE_FALSE(variant > b);
  REQUIRE_FALSE(b < variant);
  REQUIRE_FALSE(variant == b);
  REQUIRE_FALSE(b == variant);
}

template <typename T>
void checkComparisons(T low, T mid, T high) {
  checkEquals(mid, mid);
  checkGreater(mid, low);
  checkLower(mid, high);
}

TEST_CASE("JsonVariant comparisons") {
  SECTION("Double") {
    checkComparisons<double>(123.44, 123.45, 123.46);
  }

  SECTION("Float") {
    checkComparisons<float>(123.44f, 123.45f, 123.46f);
  }

  SECTION("SChar") {
    checkComparisons<signed char>(122, 123, 124);
  }

  SECTION("SInt") {
    checkComparisons<signed int>(122, 123, 124);
  }

  SECTION("SLong") {
    checkComparisons<signed long>(122L, 123L, 124L);
  }

  SECTION("SShort") {
    checkComparisons<signed short>(122, 123, 124);
  }

  SECTION("UChar") {
    checkComparisons<unsigned char>(122, 123, 124);
  }

  SECTION("UInt") {
    checkComparisons<unsigned int>(122, 123, 124);
  }

  SECTION("ULong") {
    checkComparisons<unsigned long>(122L, 123L, 124L);
  }

  SECTION("UShort") {
    checkComparisons<unsigned short>(122, 123, 124);
  }

  SECTION("null") {
    DynamicJsonDocument doc;
    JsonVariant variant = doc.to<JsonVariant>();
    variant.set(null);

    REQUIRE(variant == variant);
    REQUIRE_FALSE(variant != variant);

    REQUIRE(variant == null);
    REQUIRE_FALSE(variant != null);

    REQUIRE(variant != "null");
    REQUIRE_FALSE(variant == "null");
  }

  SECTION("StringLiteral") {
    DynamicJsonDocument doc;
    deserializeJson(doc, "\"hello\"");
    JsonVariant variant = doc.as<JsonVariant>();

    REQUIRE(variant == variant);
    REQUIRE_FALSE(variant != variant);

    REQUIRE(variant == "hello");
    REQUIRE_FALSE(variant != "hello");

    REQUIRE(variant != "world");
    REQUIRE_FALSE(variant == "world");

    REQUIRE(variant != null);
    REQUIRE_FALSE(variant == null);

    REQUIRE("hello" == variant);
    REQUIRE_FALSE("hello" != variant);

    REQUIRE("world" != variant);
    REQUIRE_FALSE("world" == variant);

    REQUIRE(null != variant);
    REQUIRE_FALSE(null == variant);
  }

  SECTION("String") {
    DynamicJsonDocument doc;
    JsonVariant variant = doc.to<JsonVariant>();
    variant.set("hello");

    REQUIRE(variant == variant);
    REQUIRE_FALSE(variant != variant);

    REQUIRE(variant == std::string("hello"));
    REQUIRE_FALSE(variant != std::string("hello"));

    REQUIRE(variant != std::string("world"));
    REQUIRE_FALSE(variant == std::string("world"));

    REQUIRE(variant != null);
    REQUIRE_FALSE(variant == null);

    REQUIRE(std::string("hello") == variant);
    REQUIRE_FALSE(std::string("hello") != variant);

    REQUIRE(std::string("world") != variant);
    REQUIRE_FALSE(std::string("world") == variant);

    REQUIRE(null != variant);
    REQUIRE_FALSE(null == variant);
  }

  DynamicJsonDocument doc1, doc2, doc3;
  JsonVariant variant1 = doc1.to<JsonVariant>();
  JsonVariant variant2 = doc2.to<JsonVariant>();
  JsonVariant variant3 = doc3.to<JsonVariant>();

  SECTION("IntegerInVariant") {
    variant1.set(42);
    variant2.set(42);
    variant3.set(666);

    REQUIRE(variant1 == variant2);
    REQUIRE_FALSE(variant1 != variant2);

    REQUIRE(variant1 != variant3);
    REQUIRE_FALSE(variant1 == variant3);
  }

  SECTION("StringInVariant") {
    variant1.set("0hello" + 1);  // make sure they have
    variant2.set("1hello" + 1);  // different addresses
    variant3.set("world");

    REQUIRE(variant1 == variant2);
    REQUIRE_FALSE(variant1 != variant2);

    REQUIRE(variant1 != variant3);
    REQUIRE_FALSE(variant1 == variant3);
  }

  SECTION("DoubleInVariant") {
    variant1.set(42.0);
    variant2.set(42.0);
    variant3.set(666.0);

    REQUIRE(variant1 == variant2);
    REQUIRE_FALSE(variant1 != variant2);

    REQUIRE(variant1 != variant3);
    REQUIRE_FALSE(variant1 == variant3);
  }

  SECTION("BoolInVariant") {
    variant1.set(true);
    variant2.set(true);
    variant3.set(false);

    REQUIRE(variant1 == variant2);
    REQUIRE_FALSE(variant1 != variant2);

    REQUIRE(variant1 != variant3);
    REQUIRE_FALSE(variant1 == variant3);
  }

  SECTION("ArrayInVariant") {
    DynamicJsonDocument docArr1, docArr2;
    JsonArray array1 = docArr1.to<JsonArray>();
    JsonArray array2 = docArr2.to<JsonArray>();

    variant1.set(array1);
    variant2.set(array1);
    variant3.set(array2);

    REQUIRE(variant1 == variant2);
    REQUIRE_FALSE(variant1 != variant2);

    REQUIRE(variant1 != variant3);
    REQUIRE_FALSE(variant1 == variant3);
  }

  SECTION("ObjectInVariant") {
    DynamicJsonDocument docObj1, docObj2;
    JsonObject obj1 = docObj1.to<JsonObject>();
    JsonObject obj2 = docObj2.to<JsonObject>();

    variant1.set(obj1);
    variant2.set(obj1);
    variant3.set(obj2);

    REQUIRE(variant1 == variant2);
    REQUIRE_FALSE(variant1 != variant2);

    REQUIRE(variant1 != variant3);
    REQUIRE_FALSE(variant1 == variant3);
  }

  // SECTION("VariantsOfDifferentTypes") {
  //   DynamicJsonDocument doc1;
  //   JsonObject obj = doc1.to<JsonObject>();

  //   DynamicJsonDocument doc2;
  //   JsonArray arr = doc2.to<JsonArray>();
  //   JsonVariant variants[] = {
  //       true, 42, 666.667, "hello", arr, obj,
  //   };
  //   size_t n = sizeof(variants) / sizeof(variants[0]);

  //   for (size_t i = 0; i < n; i++) {
  //     for (size_t j = i + 1; j < n; j++) {
  //       REQUIRE(variants[i] != variants[j]);
  //       REQUIRE_FALSE(variants[i] == variants[j]);
  //     }
  //   }
  // }
}

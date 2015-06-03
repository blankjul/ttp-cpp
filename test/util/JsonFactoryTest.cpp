#include "AbstractTest.h"
#include "util/JsonFactory.h"
#include "json/json.h"


class JsonFactoryTest : public AbstractTest {
public:
};



TEST_F(JsonFactoryTest, ToJsonTour) {
    Tour t = createTour(vector<int>{0,1,2,3});
    Json::Value result = toJson(t);
    vector<int> v;
    for(auto value : result) v.push_back(value.asInt());
    EXPECT_THAT(v, ElementsAre(0,1,2,3));
}

TEST_F(JsonFactoryTest, ToJsonMap) {
    MapPtr map = exampleMap();
    Json::Value result = toJson(*map);
}

TEST_F(JsonFactoryTest, ToJsonThiefMap) {
    ThiefMapPtr map = exampleThiefMap();
    Json::Value result = toJson(*map);
    cout << result;
}
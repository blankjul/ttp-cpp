#include "AbstractTest.h"
#include "util/JsonFactory.h"
#include "json/json.h"


class JsonParserTest : public AbstractTest {
public:
};



TEST_F(JsonParserTest, ParseJsonTour) {
    Tour t = createTour(vector<int>{0,1,2,3});
    Json::Value result;
    vector<int> v;
    for(auto value : result) v.push_back(value.asInt());
    EXPECT_THAT(v, ElementsAre(0,1,2,3));
}


#include <ctime>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Prod envionment
enum WeekDays
{
    SUNDAY = 0,
    MONDAY,
    TUESDAY,
    WEDNESDAY,
    THURSDAY,
    FRIDAY,
    SATURDAY
};

struct CalendarInterface
{
    virtual WeekDays what_day_is_today() = 0;
};

struct CalendarImplementation : public CalendarInterface
{
    WeekDays what_day_is_today() override;
};

struct Me
{
    std::unique_ptr<CalendarInterface> calendar = std::make_unique<CalendarImplementation>();

    bool can_drink_beer_today()
    {
        const auto today = calendar->what_day_is_today();
        return today == WeekDays::FRIDAY || today == WeekDays::SATURDAY;
    }
};

// Test enviroment
class MockCalendarInterface : public CalendarInterface
{
public:
    MOCK_METHOD(WeekDays, what_day_is_today, (), (override));
};

TEST(MeTest, CanNotDrinkBeerOnWednesday)
{
    auto calendar_mock = std::make_unique<::testing::StrictMock<MockCalendarInterface>>();
    EXPECT_CALL(*calendar_mock, what_day_is_today())
        .WillOnce(::testing::Return(WeekDays::WEDNESDAY));
    Me unit_under_test{std::move(calendar_mock)};

    EXPECT_FALSE(unit_under_test.can_drink_beer_today());
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

WeekDays CalendarImplementation::what_day_is_today()
{
    std::tm time_in{};
    std::time_t time_temp = std::mktime(&time_in);
    const std::tm *time_out = std::localtime(&time_temp);
    return static_cast<WeekDays>(time_out->tm_wday);
}
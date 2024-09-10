#include <twod.h>
#include <gtest/gtest.h>

TEST(TwodTest, VertexRotate) {
    twod::Vertex right(1.0f, 0.0f);
    right.rotate(45);
    EXPECT_NEAR(right.getX(), 0.7071067690849304f, 0.00001);
    EXPECT_NEAR(right.getY(), 0.7071067690849304f, 0.00001);
    right.rotate(45);
    EXPECT_NEAR(right.getX(), 0.0f, 0.00001);
    EXPECT_NEAR(right.getY(), 1.0f, 0.00001);
    right.rotate(180);
    EXPECT_NEAR(right.getX(), 0.0f, 0.00001);
    EXPECT_NEAR(right.getY(), -1.0f, 0.00001);
    right.rotate(0);
    EXPECT_NEAR(right.getX(), 0.0f, 0.00001);
    EXPECT_NEAR(right.getY(), -1.0f, 0.00001);
    right.rotate(360);
    EXPECT_NEAR(right.getX(), 0.0f, 0.00001);
    EXPECT_NEAR(right.getY(), -1.0f, 0.00001);
}

TEST(TwodTest, VertexMove) {
    twod::Vertex middle(0.0f, 0.0f);
    middle.move(1, 270);
    EXPECT_NEAR(middle.getX(), 0.0f, 0.00001);
    EXPECT_NEAR(middle.getY(), -1.0f, 0.00001);
    middle.move(0, 270);
    EXPECT_NEAR(middle.getX(), 0.0f, 0.00001);
    EXPECT_NEAR(middle.getY(), -1.0f, 0.00001);
    middle.move(1, 0);
    EXPECT_NEAR(middle.getX(), 1.0f, 0.00001);
    EXPECT_NEAR(middle.getY(), -1.0f, 0.00001);
}

TEST(TwodTest, MakeConvex) {
    std::vector<twod::Vertex> test = twod::make_convex_regular_polygon(4, 1.0f, twod::Vertex(0.0f, 0.0f));
    ASSERT_EQ(test.size(), 6);
    EXPECT_NEAR(test[0].getX(), 0.0f, 0.00001);
    EXPECT_NEAR(test[0].getY(), 0.0f, 0.00001);
    EXPECT_NEAR(test[1].getX(), 1.0f, 0.00001);
    EXPECT_NEAR(test[1].getY(), 0.0f, 0.00001);
    EXPECT_NEAR(test[2].getX(), 0.0f, 0.00001);
    EXPECT_NEAR(test[2].getY(), 1.0f, 0.00001);
    EXPECT_NEAR(test[3].getX(), -1.0f, 0.00001);
    EXPECT_NEAR(test[3].getY(), 0.0f, 0.00001);
    EXPECT_NEAR(test[4].getX(), 0.0f, 0.00001);
    EXPECT_NEAR(test[4].getY(), -1.0f, 0.00001);
    EXPECT_NEAR(test[5].getX(), 1.0f, 0.00001);
    EXPECT_NEAR(test[5].getY(), 0.0f, 0.00001);
}

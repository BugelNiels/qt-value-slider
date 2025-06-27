#include <QApplication>
#include <gtest/gtest.h>

class QtTestEnvironment : public ::testing::Environment {
  public:
    QApplication* app = nullptr;

    virtual void SetUp() {
        int argc = 0;
        char** argv = nullptr;
        app = new QApplication(argc, argv);
    }

    virtual void TearDown() {
        delete app;
        app = nullptr;
    }
};

// Register the environment
::testing::Environment* const env = ::testing::AddGlobalTestEnvironment(new QtTestEnvironment());

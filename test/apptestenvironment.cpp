#include <gtest/gtest.h>
#include <QApplication>

class QtTestEnvironment : public ::testing::Environment {
public:
    QApplication *app = nullptr;

    virtual void SetUp() {
        // Create a QApplication instance
        int argc = 0;
        char **argv = nullptr; // Adjust if you need command line arguments
        app = new QApplication(argc, argv);
    }

    virtual void TearDown() {
        // Clean up the QApplication instance
        delete app;
        app = nullptr;
    }
};

// Register the environment
::testing::Environment *const env = ::testing::AddGlobalTestEnvironment(new QtTestEnvironment());

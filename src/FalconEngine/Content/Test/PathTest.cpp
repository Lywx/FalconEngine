#include <iostream>
#include <string>

#include <catch.hpp>

#include <FalconEngine/Content/Path.h>

namespace FalconEngine {

using namespace std;

TEST_CASE("Path Test", "")
{
    auto cwd = GetCurrentPath();
    string cwdString(cwd.begin(), cwd.end());

    INFO(L"Current Path: " << cwdString);

    SECTION("Getting test filename (make sure you've created it first)")
    {
        REQUIRE(GetFileName(L"Test\\TestResource.dat") == wstring(L"TestResource.dat"));
    }

    SECTION("Getting file size", "")
    {
        REQUIRE(int(GetFileSize(L"Test\\TestResource.dat")) == 1349434);
    }

    SECTION("Checking if file exists", "")
    {
        REQUIRE(Exists(L"Test\\TestResource.dat") == true);
    }

    SECTION("Checking if file (fake) exists", "")
    {
        REQUIRE(Exists(L"Test\\TestResource.dat_") == false);
    }

    SECTION("Creating directory", "")
    {
        REQUIRE(CreateDirectory(L"Test\\TestDirectory") == true);
    }
}

}
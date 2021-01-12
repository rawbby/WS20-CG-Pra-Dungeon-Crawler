#pragma once

#include <cstdlib>
#include <spdlog/spdlog.h>

int main (int argc, char *argv[])
{
    if (argc < 2)
    {
        spdlog::error("INSUFFICIENT ARGUMENTS! REQUIRED 1");
    }

    return EXIT_SUCCESS;
}

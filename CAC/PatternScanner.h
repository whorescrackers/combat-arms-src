#pragma once
DWORD PatternScan(DWORD dwModuleBase, CONST CHAR* szSignature, BOOL bSkipFirst)
{
    static auto patternToByte = [](CONST CHAR* szPattern)
    {
        auto       bytes = std::vector<int>{};
        const auto start = const_cast<char*>(szPattern);
        const auto end = const_cast<char*>(szPattern) + strlen(szPattern);

        for (auto current = start; current < end; ++current)
        {
            if (*current == '?')
            {
                ++current;
                if (*current == '?')
                    ++current;
                bytes.push_back(-1);
            }
            else {
                bytes.push_back(strtoul(current, &current, 16));
            }
        }

        return bytes;
    };

    const auto dosHeader = (PIMAGE_DOS_HEADER)dwModuleBase;
    const auto ntHeaders = (PIMAGE_NT_HEADERS)((PBYTE)dwModuleBase + dosHeader->e_lfanew);

    const auto sizeOfImage = ntHeaders->OptionalHeader.SizeOfImage;
    auto       patternBytes = patternToByte(szSignature);
    const auto scanBytes = reinterpret_cast<PBYTE>(dwModuleBase);

    const auto s = patternBytes.size();
    const auto d = patternBytes.data();

    bool bFoundFirst = false;

    for (auto i = 0ul; i < sizeOfImage - s; ++i)
    {
        bool found = true;

        for (auto j = 0ul; j < s; ++j)
        {
            if (scanBytes[i + j] != d[j] && d[j] != -1)
            {
                found = false;
                break;
            }
        }

        if (found)
        {
            if (bSkipFirst)
            {
                if (!bFoundFirst)
                    bFoundFirst = true;
                else
                {
                    return reinterpret_cast<DWORD>(&scanBytes[i]); // Return 2th Result.
                }
            }
            else
            {
                return reinterpret_cast<DWORD>(&scanBytes[i]); // Return First Result.
            }
        }
    }

    return 0;
}
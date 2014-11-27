//-----------------------------------------------------------------------------
/** @file twogtp/Analyze.cpp
    @author Markus Enzenberger
    @copyright GNU General Public License version 3 or later */
//-----------------------------------------------------------------------------

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "Analyze.h"

#include <fstream>
#include <map>
#include <regex>
#include "libboardgame_util/Exception.h"
#include "libboardgame_util/FmtSaver.h"
#include "libboardgame_util/Statistics.h"
#include "libboardgame_util/StringUtil.h"

using libboardgame_util::from_string;
using libboardgame_util::split;
using libboardgame_util::trim;
using libboardgame_util::Exception;
using libboardgame_util::FmtSaver;
using libboardgame_util::Statistics;
using libboardgame_util::StatisticsExt;

//-----------------------------------------------------------------------------

namespace {

void write_result(const Statistics<>& stat)
{
    FmtSaver saver(cout);
    cout << fixed << setprecision(1) << stat.get_mean() * 100 << "+-"
         << stat.get_error() * 100;
}

} // namespace

//-----------------------------------------------------------------------------

void analyze(const string& file)
{
    ifstream in(file);
    Statistics<> stat_result;
    map<unsigned, Statistics<>> stat_result_player;
    map<float, unsigned> result_count;
    StatisticsExt<> stat_length;
    StatisticsExt<> stat_cpu_b;
    StatisticsExt<> stat_cpu_w;
    string line;
    while (getline(in, line))
    {
        line = trim(line);
        if (! line.empty() && line[0] == '#')
            continue;
        auto columns = split(line, '\t');
        if (columns.empty())
            continue;
        float result;
        unsigned length;
        unsigned player;
        float cpu_b;
        float cpu_w;
        if (columns.size() != 6
                || ! from_string(columns[1], result)
                || ! from_string(columns[2], length)
                || ! from_string(columns[3], player)
                || ! from_string(columns[4], cpu_b)
                || ! from_string(columns[5], cpu_w))
            throw Exception("invalid format");
        stat_result.add(result);
        stat_result_player[player].add(result);
        ++result_count[result];
        stat_length.add(length);
        stat_cpu_b.add(cpu_b);
        stat_cpu_w.add(cpu_w);
    }
    auto count = stat_result.get_count();
    cout << "Gam: " << count;
    if (count == 0)
    {
        cout << '\n';
        return;
    }
    cout << ", Res: ";
    write_result(stat_result);
    cout << " (";
    bool is_first = true;
    for (auto& i : stat_result_player)
    {
        if (! is_first)
            cout << ", ";
        else
            is_first = false;
        cout << i.first << ": ";
        write_result(i.second);
    }
    cout << ")\nResFreq:";
    for (auto& i : result_count)
    {
        cout << ' ' << i.first << "=";
        {
            FmtSaver saver(cout);
            auto fraction = i.second / count;
            cout << fixed << setprecision(1) << fraction * 100
                 << "%+-" << sqrt(fraction * (1 - fraction) / count) * 100
                 << '%';
        }
    }
    cout << "\nCpuB: ";
    stat_cpu_b.write(cout, true, 3);
    cout << "\nCpuW: ";
    stat_cpu_w.write(cout, true, 3);
    cout << "\nLen: " << fixed << setprecision(1) << stat_length.get_mean()
         << " dev=" << stat_length.get_deviation() << " min="
         << setprecision(0) << stat_length.get_min() << " max="
         << stat_length.get_max() << '\n';
}

void splitsgf(const string& file)
{
    ifstream in(file);
    string filename;
    string buffer;
    regex pattern("GN\\[(\\d+)\\]");
    string line;
    while (getline(in, line))
    {
        if (trim(line) == "(")
        {
            if (! filename.empty())
            {
                ofstream out(filename);
                out << buffer;
            }
            buffer.clear();
        }
        else
        {
            smatch match;
            regex_search(line, match, pattern);
            if (! match.empty())
                filename = string(match[1]) + ".blksgf";
        }
        buffer.append(line);
        buffer.append("\n");
    }
    if (! filename.empty())
    {
        ofstream out(filename);
        out << buffer;
    }
}

//-----------------------------------------------------------------------------
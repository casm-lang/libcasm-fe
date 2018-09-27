//
//  Copyright (C) 2014-2018 CASM Organization <https://casm-lang.org>
//  All rights reserved.
//
//  Developed by: Philipp Paulweber
//                Emmanuel Pescosta
//                Florian Hahn
//                <https://github.com/casm-lang/libcasm-fe>
//
//  This file is part of libcasm-fe.
//
//  libcasm-fe is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  libcasm-fe is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with libcasm-fe. If not, see <http://www.gnu.org/licenses/>.
//
//  Additional permission under GNU GPL version 3 section 7
//
//  libcasm-fe is distributed under the terms of the GNU General Public License
//  with the following clarification and special exception: Linking libcasm-fe
//  statically or dynamically with other modules is making a combined work
//  based on libcasm-fe. Thus, the terms and conditions of the GNU General
//  Public License cover the whole combination. As a special exception,
//  the copyright holders of libcasm-fe give you permission to link libcasm-fe
//  with independent modules to produce an executable, regardless of the
//  license terms of these independent modules, and to copy and distribute
//  the resulting executable under terms of your choice, provided that you
//  also meet, for each linked independent module, the terms and conditions
//  of the license of that module. An independent module is a module which
//  is not derived from or based on libcasm-fe. If you modify libcasm-fe, you
//  may extend this exception to your version of the library, but you are
//  not obliged to do so. If you do not wish to do so, delete this exception
//  statement from your version.
//

#include "HashMapBase.h"

#ifdef HASH_MAP_PERF
#include <iostream>
#endif

namespace details
{
    std::size_t nextPowerOfTwo( std::size_t n ) noexcept
    {
        n -= 1;
        n |= ( n >> 1 );
        n |= ( n >> 2 );
        n |= ( n >> 4 );
        n |= ( n >> 8 );
        n |= ( n >> 16 );
#if __SIZEOF_SIZE_T__ > 4
        n |= ( n >> 32 );
#endif
        return n + 1;
    }

    std::size_t nextPrime( std::size_t n ) noexcept
    {
        static const std::size_t unfoldedPrimes[] = { 2, 2, 3, 5, 5, 7, 7, 11, 11, 11, 11, 13, 13 };

        static const std::size_t primes[] = {
            17ULL,
            19ULL,
            23ULL,
            29ULL,
            31ULL,
            37ULL,
            41ULL,
            43ULL,
            47ULL,
            53ULL,
            59ULL,
            61ULL,
            67ULL,
            71ULL,
            73ULL,
            79ULL,
            83ULL,
            89ULL,
            97ULL,
            103ULL,
            109ULL,
            113ULL,
            127ULL,
            137ULL,
            139ULL,
            149ULL,
            157ULL,
            167ULL,
            179ULL,
            193ULL,
            199ULL,
            211ULL,
            227ULL,
            241ULL,
            257ULL,
            277ULL,
            293ULL,
            313ULL,
            337ULL,
            359ULL,
            383ULL,
            409ULL,
            439ULL,
            467ULL,
            503ULL,
            541ULL,
            577ULL,
            619ULL,
            661ULL,
            709ULL,
            761ULL,
            823ULL,
            887ULL,
            953ULL,
            1031ULL,
            1109ULL,
            1193ULL,
            1289ULL,
            1381ULL,
            1493ULL,
            1613ULL,
            1741ULL,
            1879ULL,
            2029ULL,
            2179ULL,
            2357ULL,
            2549ULL,
            2753ULL,
            2971ULL,
            3209ULL,
            3469ULL,
            3739ULL,
            4027ULL,
            4349ULL,
            4703ULL,
            5087ULL,
            5503ULL,
            5953ULL,
            6427ULL,
            6949ULL,
            7517ULL,
            8123ULL,
            8783ULL,
            9497ULL,
            10273ULL,
            11113ULL,
            12011ULL,
            12983ULL,
            14033ULL,
            15173ULL,
            16411ULL,
            17749ULL,
            19183ULL,
            20753ULL,
            22447ULL,
            24281ULL,
            26267ULL,
            28411ULL,
            30727ULL,
            33223ULL,
            35933ULL,
            38873ULL,
            42043ULL,
            45481ULL,
            49201ULL,
            53201ULL,
            57557ULL,
            62233ULL,
            67307ULL,
            72817ULL,
            78779ULL,
            85229ULL,
            92203ULL,
            99733ULL,
            107897ULL,
            116731ULL,
            126271ULL,
            136607ULL,
            147793ULL,
            159871ULL,
            172933ULL,
            187091ULL,
            202409ULL,
            218971ULL,
            236897ULL,
            256279ULL,
            277261ULL,
            299951ULL,
            324503ULL,
            351061ULL,
            379787ULL,
            410857ULL,
            444487ULL,
            480881ULL,
            520241ULL,
            562841ULL,
            608903ULL,
            658753ULL,
            712697ULL,
            771049ULL,
            834181ULL,
            902483ULL,
            976369ULL,
            1056323ULL,
            1142821ULL,
            1236397ULL,
            1337629ULL,
            1447153ULL,
            1565659ULL,
            1693859ULL,
            1832561ULL,
            1982627ULL,
            2144977ULL,
            2320627ULL,
            2510653ULL,
            2716249ULL,
            2938679ULL,
            3179303ULL,
            3439651ULL,
            3721303ULL,
            4026031ULL,
            4355707ULL,
            4712381ULL,
            5098259ULL,
            5515729ULL,
            5967347ULL,
            6456007ULL,
            6984629ULL,
            7556579ULL,
            8175383ULL,
            8844859ULL,
            9569143ULL,
            10352717ULL,
            11200489ULL,
            12117689ULL,
            13109983ULL,
            14183539ULL,
            15345007ULL,
            16601593ULL,
            17961079ULL,
            19431899ULL,
            21023161ULL,
            22744717ULL,
            24607243ULL,
            26622317ULL,
            28802401ULL,
            31160981ULL,
            33712729ULL,
            36473443ULL,
            39460231ULL,
            42691603ULL,
            46187573ULL,
            49969847ULL,
            54061849ULL,
            58488943ULL,
            63278561ULL,
            68460391ULL,
            74066549ULL,
            80131819ULL,
            86693767ULL,
            93793069ULL,
            101473717ULL,
            109783337ULL,
            118773397ULL,
            128499677ULL,
            139022417ULL,
            150406843ULL,
            162723577ULL,
            176048909ULL,
            190465427ULL,
            206062531ULL,
            222936881ULL,
            241193053ULL,
            260944219ULL,
            282312799ULL,
            305431229ULL,
            330442829ULL,
            357502601ULL,
            386778277ULL,
            418451333ULL,
            452718089ULL,
            489790921ULL,
            529899637ULL,
            573292817ULL,
            620239453ULL,
            671030513ULL,
            725980837ULL,
            785430967ULL,
            849749479ULL,
            919334987ULL,
            994618837ULL,
            1076067617ULL,
            1164186217ULL,
            1259520799ULL,
            1362662261ULL,
            1474249943ULL,
            1594975441ULL,
            1725587117ULL,
            1866894511ULL,
            2019773507ULL,
            2185171673ULL,
            2364114217ULL,
            2557710269ULL,
            2767159799ULL,
            2993761039ULL,
            3238918481ULL,
            3504151727ULL,
            3791104843ULL,
            4101556399ULL,
            4294967291ULL,
#if __SIZEOF_SIZE_T__ > 4
            6442450933ULL,
            8589934583ULL,
            12884901857ULL,
            17179869143ULL,
            25769803693ULL,
            34359738337ULL,
            51539607367ULL,
            68719476731ULL,
            103079215087ULL,
            137438953447ULL,
            206158430123ULL,
            274877906899ULL,
            412316860387ULL,
            549755813881ULL,
            824633720731ULL,
            1099511627689ULL,
            1649267441579ULL,
            2199023255531ULL,
            3298534883309ULL,
            4398046511093ULL,
            6597069766607ULL,
            8796093022151ULL,
            13194139533241ULL,
            17592186044399ULL,
            26388279066581ULL,
            35184372088777ULL,
            52776558133177ULL,
            70368744177643ULL,
            105553116266399ULL,
            140737488355213ULL,
            211106232532861ULL,
            281474976710597ULL,
            562949953421231ULL,
            1125899906842597ULL,
            2251799813685119ULL,
            4503599627370449ULL,
            9007199254740881ULL,
            18014398509481951ULL,
            36028797018963913ULL,
            72057594037927931ULL,
            144115188075855859ULL,
            288230376151711717ULL,
            576460752303423433ULL,
            1152921504606846883ULL,
            2305843009213693951ULL,
            4611686018427387847ULL,
            9223372036854775783ULL,
            18446744073709551557ULL,
            18446744073709551557ULL
#endif
        };

        constexpr auto unfoldedPrimesCount = sizeof( unfoldedPrimes ) / sizeof( char );
        constexpr auto primesCount = sizeof( primes ) / sizeof( unsigned long );

        constexpr auto firstPrime = primes;
        constexpr auto lastPrime = primes + primesCount - 1;

        if( n < unfoldedPrimesCount )
        {
            return unfoldedPrimes[ n ];
        }
        else
        {
            return *std::lower_bound( firstPrime, lastPrime, n + 1 );
        }
    }
}

#ifdef HASH_MAP_PERF

void HashMapPerformanceStatistics::probedOnSearch( std::size_t probeSequenceLength ) const
{
    m_longestSearchProbeSequenceLength =
        libstdhl::Math::max( m_longestSearchProbeSequenceLength, probeSequenceLength );
    m_cumulativeSearchProbeSequenceLength += probeSequenceLength;

    overallStatistics().m_longestSearchProbeSequenceLength = libstdhl::Math::max(
        overallStatistics().m_longestSearchProbeSequenceLength, probeSequenceLength );
    overallStatistics().m_cumulativeSearchProbeSequenceLength += probeSequenceLength;
}

void HashMapPerformanceStatistics::probedOnInsert( std::size_t probeSequenceLength ) const
{
    m_longestInsertProbeSequenceLength =
        libstdhl::Math::max( m_longestInsertProbeSequenceLength, probeSequenceLength );
    m_cumulativeInsertProbeSequenceLength += probeSequenceLength;

    overallStatistics().m_longestInsertProbeSequenceLength = libstdhl::Math::max(
        overallStatistics().m_longestInsertProbeSequenceLength, probeSequenceLength );
    overallStatistics().m_cumulativeInsertProbeSequenceLength += probeSequenceLength;
}

void HashMapPerformanceStatistics::searched() const
{
    ++m_numberOfSearches;
    ++overallStatistics().m_numberOfSearches;
}

void HashMapPerformanceStatistics::inserted() const
{
    ++m_numberOfInsertions;
    ++overallStatistics().m_numberOfInsertions;
}

void HashMapPerformanceStatistics::resized() const
{
    ++m_numberOfResizes;
    ++overallStatistics().m_numberOfResizes;
}

void HashMapPerformanceStatistics::unsuccessfulSearch() const
{
    ++m_numberOfUnsuccessfulSearches;
    ++overallStatistics().m_numberOfUnsuccessfulSearches;
}

void HashMapPerformanceStatistics::read() const
{
    ++m_numberOfReads;
    ++overallStatistics().m_numberOfReads;
}

void HashMapPerformanceStatistics::write() const
{
    ++m_numberOfWrites;
    ++overallStatistics().m_numberOfWrites;
}

std::size_t HashMapPerformanceStatistics::longestSearchProbeSequenceLength() const
{
    return m_longestSearchProbeSequenceLength;
}

std::size_t HashMapPerformanceStatistics::cumulativeSearchProbeSequenceLength() const
{
    return m_cumulativeSearchProbeSequenceLength;
}

std::size_t HashMapPerformanceStatistics::longestInsertProbeSequenceLength() const
{
    return m_longestInsertProbeSequenceLength;
}

std::size_t HashMapPerformanceStatistics::cumulativeInsertProbeSequenceLength() const
{
    return m_cumulativeInsertProbeSequenceLength;
}

std::size_t HashMapPerformanceStatistics::numberOfSearches() const
{
    return m_numberOfSearches;
}

std::size_t HashMapPerformanceStatistics::numberOfInsertions() const
{
    return m_numberOfInsertions;
}

std::size_t HashMapPerformanceStatistics::numberOfResizes() const
{
    return m_numberOfResizes;
}

std::size_t HashMapPerformanceStatistics::numberOfUnsuccessfulSearches() const
{
    return m_numberOfUnsuccessfulSearches;
}

std::size_t HashMapPerformanceStatistics::numberOfReads() const
{
    return m_numberOfReads;
}

std::size_t HashMapPerformanceStatistics::numberOfWrites() const
{
    return m_numberOfWrites;
}

HashMapPerformanceStatistics& HashMapPerformanceStatistics::overallStatistics()
{
    static HashMapPerformanceStatistics overallStatistics;
    return overallStatistics;
}

std::ostream& operator<<( std::ostream& stream, const HashMapPerformanceStatistics& statistics )
{
    stream << "HashMap Performance Statistics:" << std::endl
           << " - Longest search probe sequence length: "
           << std::to_string( statistics.longestSearchProbeSequenceLength() ) << std::endl
           << " - Cumulative search probe sequence length: "
           << std::to_string( statistics.cumulativeSearchProbeSequenceLength() ) << std::endl
           << " - Longest insert probe sequence length: "
           << std::to_string( statistics.longestInsertProbeSequenceLength() ) << std::endl
           << " - Cumulative insert probe sequence length: "
           << std::to_string( statistics.cumulativeInsertProbeSequenceLength() ) << std::endl
           << " - Number of searches: " << std::to_string( statistics.numberOfSearches() )
           << std::endl
           << " - Number of insertions: " << std::to_string( statistics.numberOfInsertions() )
           << std::endl
           << " - Number of resizes: " << std::to_string( statistics.numberOfResizes() )
           << std::endl
           << " - Number of unsuccessful searches: "
           << std::to_string( statistics.numberOfUnsuccessfulSearches() ) << std::endl
           << " - Number of reads: " << std::to_string( statistics.numberOfReads() ) << std::endl
           << " - Number of writes: " << std::to_string( statistics.numberOfWrites() ) << std::endl;

    return stream;
}

#endif

// Copyright (c) 2009-2012 The Bitcoin developers
// Copyright (c) 2011-2012 Litecoin Developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/foreach.hpp>

#include "checkpoints.h"

#include "main.h"
#include "uint256.h"

namespace Checkpoints
{
    typedef std::map<int, uint256> MapCheckpoints;

    //
    // What makes a good checkpoint block?
    // + Is surrounded by blocks with reasonable timestamps
    //   (no blocks before with a timestamp after, none after with
    //    timestamp before)
    // + Contains no strange transactions
    //
    static MapCheckpoints mapCheckpoints =
        boost::assign::map_list_of // Yo dawg, this is the secret. Checkpoint 0 hash == Genesis block hash.
        (         0, uint256("0x68f6283d61e7f8b6ae0965d8873743197c72e5f54a447c9977d714cfa45b5d9c"))
		(		10, uint256("0x1b3feeb4b16f99f70e1e771fba02a3fe53b20d56aecb47f28048ce2db08e70f8"))
		(	  100, uint256("0xe983b944095453f9487b9336dbe659dfb455a549669a18c6608a30780df3ab7e"))
		(	1000, uint256("0x8566f7d66d641e190b8a0f7cc25ad178d23f4e025954d116ef140f4bcf14f19f"))
		( 15500, uint256("0xe91a5d966f676dfac6cda463dc569cb4c7f478c943455a1026e0e44cb4236cf2"))
		( 25000, uint256("0x1d81a5862e8774a777fdddf3d057be6326bc663150a73d4ab88d5b3262d1e8b3"))
		( 31000, uint256("0xa1d1eb5f65d730e4433d6d22dae63433aadab295d719c218faca87fff7a4fba3"))
		;
		
	 

    bool CheckBlock(int nHeight, const uint256& hash)
    {
        if (fTestNet) return true; // Testnet has no checkpoints

        MapCheckpoints::const_iterator i = mapCheckpoints.find(nHeight);
        if (i == mapCheckpoints.end()) return true;
        return hash == i->second;
    }

    int GetTotalBlocksEstimate()
    {
        if (fTestNet) return 0;
        return mapCheckpoints.rbegin()->first;
    }

    CBlockIndex* GetLastCheckpoint(const std::map<uint256, CBlockIndex*>& mapBlockIndex)
    {
        if (fTestNet) return NULL;

        BOOST_REVERSE_FOREACH(const MapCheckpoints::value_type& i, mapCheckpoints)
        {
            const uint256& hash = i.second;
            std::map<uint256, CBlockIndex*>::const_iterator t = mapBlockIndex.find(hash);
            if (t != mapBlockIndex.end())
                return t->second;
        }
        return NULL;
    }
}

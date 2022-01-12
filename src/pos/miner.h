// Copyright (c) 2017-2021 The Particl Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef PARTICL_POS_MINER_H
#define PARTICL_POS_MINER_H

#include <thread>
#include <threadinterrupt.h>
#include <atomic>
#include <vector>
#include <string>

namespace wallet {
struct WalletContext;
class CWallet;
} // namespace wallet
class ChainstateManager;
class CBlockIndex;
class CBlock;

class CHDWallet;

class StakeThread
{
public:
    StakeThread() {};
    std::thread thread;
    std::string sName;
    CThreadInterrupt m_thread_interrupt;
};

extern std::vector<StakeThread*> vStakeThreads;

extern std::atomic<bool> fIsStaking;

extern int nMinStakeInterval;
extern int nMinerSleep;

bool CheckStake(ChainstateManager &chainman, const CBlock *pblock);

void StartThreadStakeMiner(wallet::WalletContext &wallet_context, ChainstateManager &chainman);
void StopThreadStakeMiner();
void WakeThreadStakeMiner(CHDWallet *pwallet);
bool ThreadStakeMinerStopped();

void ThreadStakeMiner(size_t nThreadID, std::vector<std::shared_ptr<wallet::CWallet>> &vpwallets, size_t nStart, size_t nEnd, ChainstateManager *chainman);

#endif // PARTICL_POS_MINER_H

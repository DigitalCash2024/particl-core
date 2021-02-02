// Copyright (c) 2017-2020 The Particl Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <wallet/test/hdwallet_test_fixture.h>

#include <rpc/server.h>
#include <wallet/db.h>
#include <wallet/hdwallet.h>
#include <wallet/rpcwallet.h>
#include <validation.h>
#include <util/system.h>
#include <blind.h>

HDWalletTestingSetup::HDWalletTestingSetup(const std::string &chainName):
    TestingSetup(chainName, {}, true) // fParticlMode = true
{
    ECC_Start_Stealth();
    ECC_Start_Blinding();

    bool fFirstRun;
    pwalletMain = std::make_shared<CHDWallet>(m_chain.get(), "", CreateMockWalletDatabase());
    AddWallet(pwalletMain);
    pwalletMain->LoadWallet(fFirstRun);
    m_chain_notifications_handler = m_chain->handleNotifications({ pwalletMain.get(), [](CHDWallet*) {} });
    m_wallet_client->registerRpcs();
}

HDWalletTestingSetup::~HDWalletTestingSetup()
{
    RemoveWallet(pwalletMain, nullopt);
    pwalletMain->Finalise();
    pwalletMain.reset();

    particl::mapStakeSeen.clear();
    particl::listStakeSeen.clear();

    ECC_Stop_Stealth();
    ECC_Stop_Blinding();
}

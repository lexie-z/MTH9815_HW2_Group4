/**
 * productservice.hpp defines Bond and IRSwap ProductServices
 */

#include <iostream>
#include <map>
#include "products.hpp"
#include "soa.hpp"
#include <vector>

/**
 * Bond Product Service to own reference data over a set of bond securities.
 * Key is the productId string, value is a Bond.
 */
class BondProductService : public Service<string,Bond>
{

public:
  // BondProductService ctor
  BondProductService();

  // Return the bond data for a particular bond product identifier
  Bond& GetData(string productId);

  // Add a bond to the service (convenience method)
  void Add(Bond &bond);

  // Get all Bonds with the specified ticker
  vector<Bond> GetBonds(const string& _ticker) const;

private:
  map<string,Bond> bondMap; // cache of bond products

};

/**
 * Interest Rate Swap Product Service to own reference data over a set of IR Swap products
 * Key is the productId string, value is a IRSwap.
 */
class IRSwapProductService : public Service<string,IRSwap>
{
public:
  // IRSwapProductService ctor
  IRSwapProductService();

  // Return the IR Swap data for a particular bond product identifier
  IRSwap& GetData(string productId);

  // Add a bond to the service (convenience method)
  void Add(IRSwap &swap);

  // Get all Swaps with the specified fixed leg day count convention
  vector<IRSwap> GetSwaps(DayCountConvention _fixedLegDayCountConvention) const;

  // Get all Swaps with the specified fixed leg payment frequency
  vector<IRSwap> GetSwaps(PaymentFrequency _fixedLegPaymentFrequency) const;

  // Get all Swaps with the specified floating index
  vector<IRSwap> GetSwaps(FloatingIndex _floatingIndex) const;

  // Get all Swaps with a term in years greater than the specified value
  vector<IRSwap> GetSwapsGreaterThan(int _termYears) const;

  // Get all Swaps with a term in years less than the specified value
  vector<IRSwap> GetSwapsLessThan(int _termYears) const;

  // Get all Swaps with the specified swap type
  vector<IRSwap> GetSwaps(SwapType _swapType) const;

  // Get all Swaps with the specified swap leg type
  vector<IRSwap> GetSwaps(SwapLegType _swapLegType) const;

private:
  map<string,IRSwap> swapMap; // cache of IR Swap products

};

/**
 * Future Product Service to own reference data over a set of future products
 * Key is the productId string, value is a future.
 */

class FutureProductService : public Service<string,Future> {
public:
    // FutureProductService ctor
    FutureProductService();

    // Return the future data for a particular future product identifier
    Future& GetData(string productId);

    // Add a future to the service (convenience method)
    void Add(Future &future);

private:
    map<string,Future> futureMap; // cache of future products
};

BondProductService::BondProductService()
{
  bondMap = map<string,Bond>();
}

Bond& BondProductService::GetData(string productId)
{
  return bondMap[productId];
}

void BondProductService::Add(Bond &bond)
{
  bondMap.insert(pair<string,Bond>(bond.GetProductId(), bond));
}

IRSwapProductService::IRSwapProductService()
{
  swapMap = map<string,IRSwap>();
}

IRSwap& IRSwapProductService::GetData(string productId)
{
  return swapMap[productId];
}

void IRSwapProductService::Add(IRSwap &swap)
{
  swapMap.insert(pair<string,IRSwap>(swap.GetProductId(), swap));
}

FutureProductService::FutureProductService()
{
    futureMap = map<string,Future>();
}

Future& FutureProductService::GetData(string productId)
{
    return futureMap[productId];
}

void FutureProductService::Add(Future &future)
{
    futureMap.insert(pair<string,Future>(future.GetProductId(), future));
}

vector<Bond> BondProductService::GetBonds(const string &_ticker) const {
    vector<Bond> res;

    for (auto [key, val] : bondMap) {
        if (val.GetTicker() == _ticker) {
            res.push_back(val);
        }
    }

    return res;
}

// Get all Swaps with the specified fixed leg day count convention
vector<IRSwap> IRSwapProductService::GetSwaps(DayCountConvention _fixedLegDayCountConvention) const {
    vector<IRSwap> res;

    for (auto [key, val] : swapMap) {
        if (val.GetFixedLegDayCountConvention() == _fixedLegDayCountConvention) {
            res.push_back(val);
        }
    }

    return res;
}

// Get all Swaps with the specified fixed leg payment frequency
vector<IRSwap> IRSwapProductService::GetSwaps(PaymentFrequency _fixedLegPaymentFrequency) const {
    vector<IRSwap> res;

    for (auto [key, val] : swapMap) {
        if (val.GetFixedLegPaymentFrequency() == _fixedLegPaymentFrequency) {
            res.push_back(val);
        }
    }

    return res;
}


// Get all Swaps with the specified floating index
vector<IRSwap> IRSwapProductService::GetSwaps(FloatingIndex _floatingIndex) const {
    vector<IRSwap> res;

    for (auto [key, val] : swapMap) {
        if (val.GetFloatingIndex() == _floatingIndex) {
            res.push_back(val);
        }
    }

    return res;
}

// Get all Swaps with a term in years greater than the specified value
vector<IRSwap> IRSwapProductService::GetSwapsGreaterThan(int _termYears) const {
    vector<IRSwap> res;

    for (auto [key, val] : swapMap) {
        if (val.GetTermYears() > _termYears) {
            res.push_back(val);
        }
    }

    return res;
}

// Get all Swaps with a term in years less than the specified value
vector<IRSwap> IRSwapProductService::GetSwapsLessThan(int _termYears) const {
    vector<IRSwap> res;

    for (auto [key, val] : swapMap) {
        if (val.GetTermYears() < _termYears) {
            res.push_back(val);
        }
    }

    return res;
}


// Get all Swaps with the specified swap type
vector<IRSwap> IRSwapProductService::GetSwaps(SwapType _swapType) const {
    vector<IRSwap> res;

    for (auto [key, val] : swapMap) {
        if (val.GetSwapType() == _swapType) {
            res.push_back(val);
        }
    }

    return res;
}


// Get all Swaps with the specified swap leg type
vector<IRSwap> IRSwapProductService::GetSwaps(SwapLegType _swapLegType) const {
    vector<IRSwap> res;

    for (auto [key, val] : swapMap) {
        if (val.GetSwapLegType() == _swapLegType) {
            res.push_back(val);
        }
    }

    return res;
}
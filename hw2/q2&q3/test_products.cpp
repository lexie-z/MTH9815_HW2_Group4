/**
 * test program for our ProductServices
 */

#include <iostream>
#include <vector>
#include "products.hpp"
#include "productservice.hpp"

using namespace std;

void TestFutureProductService() {
    // Create a FutureProductService
    FutureProductService futureProductService;

    // Create a 2Y coal future
    date coal_maturityDate(2025, Dec, 5);
    string coal_id("C2C5");
    Future coal_future(coal_id, "Coal", coal_maturityDate);

    // Add the 2-year coal future to the FutureProductService
    futureProductService.Add(coal_future);

    // Create a 8Y treasury note and a bond future with the bond as the underlying asset.
    date bond_maturityDate(2031, Dec, 5);
    string cusip = "912828M70";
    Bond treasuryBond(cusip, CUSIP, "T", 2.25, bond_maturityDate);

    std::string bond_future_id("XYZ123");
    date bond_future_maturity(2024, Jan, 15);
    BondFuture bond_future(bond_future_id, &treasuryBond, bond_future_maturity);

    // Add the bond future to the FutureProductService
    futureProductService.Add(bond_future);

    // Create a 5Y eurodollar future
    date eurodollar_maturityDate(2028, Dec, 5);
    string eurodollar_future_id("GEZ5");
    EuroDollarFuture eurodollar_future(eurodollar_future_id, eurodollar_maturityDate);

    // Add the 5-year eurodollar future to the FutureProductService
    futureProductService.Add(eurodollar_future);

    // Validate the futures
    Future retrieved_coal_future = futureProductService.GetData(coal_id);
    assert(retrieved_coal_future.GetProductId() == coal_id);

    Future retrieved_bond_future = futureProductService.GetData(bond_future_id);
    assert(retrieved_bond_future.GetProductId() == bond_future_id);

    Future retrieved_eurodollar_future = futureProductService.GetData(eurodollar_future_id);
    assert(retrieved_eurodollar_future.GetProductId() == eurodollar_future_id);

    // Print retrieved futures
    std::cout << "2-Year Coal Future ID: " << retrieved_coal_future.GetProductId() << " ==> " << retrieved_coal_future << std::endl;
    std::cout << "Bond Future ID: " << retrieved_bond_future.GetProductId() << " ==> " << retrieved_bond_future << std::endl;
    std::cout << "5-Year Eurodollar Future ID: " << retrieved_eurodollar_future.GetProductId() << " ==> " << retrieved_eurodollar_future << std::endl;
}

void TestBondProductService() {
    // Create the 10Y treasury note
    date maturityDate(2025, Nov, 16);
    string cusip = "912828M56";
    Bond treasuryBond(cusip, CUSIP, "T", 2.25, maturityDate);

    // Create the 2Y treasury note
    date maturityDate2(2017, Nov, 5);
    string cusip2 = "912828TW0";
    Bond treasuryBond2(cusip2, CUSIP, "T", 0.75, maturityDate2);

    // Create a BondProductService
    BondProductService *bondProductService = new BondProductService();

    // Add the 10Y note to the BondProductService and retrieve it from the ervice
    bondProductService->Add(treasuryBond);
    Bond bond = bondProductService->GetData(cusip);
    cout << "CUSIP: " << bond.GetProductId() << " ==> " << bond << endl;

    // Add the 2Y note to the BondProductService and retrieve it from the service
    bondProductService->Add(treasuryBond2);
    bond = bondProductService->GetData(cusip2);
    cout << "CUSIP: " << bond.GetProductId() << " ==> " << bond << endl;

    // Test GetBonds
    cout << "\nGet all Bonds with ticker = T\n";
    vector<Bond> res = bondProductService->GetBonds("T");
    for (const auto& b : res) {
        cout << b << "\n";
    }
    delete bondProductService;
}

void TestIRswapProductService() {
    // Create the Spot 10Y Outright Swap
    date effectiveDate(2015, Nov, 16);
    date terminationDate(2025, Nov, 16);
    string outright10Y = "Spot-Outright-10Y";
    IRSwap outright10YSwap(outright10Y, THIRTY_THREE_SIXTY, THIRTY_THREE_SIXTY, SEMI_ANNUAL, LIBOR, TENOR_1M, effectiveDate, terminationDate, USD, 10, SPOT, OUTRIGHT);

    // Create the IMM 2Y Outright Swap
    date effectiveDate2(2015, Dec, 20);
    date terminationDate2(2017, Dec, 20);
    string imm2Y = "FORWARD-Curve-2Y";
    IRSwap imm2YSwap(imm2Y, THIRTY_THREE_SIXTY, THIRTY_THREE_SIXTY, ANNUAL, LIBOR, TENOR_3M, effectiveDate2, terminationDate2, USD, 2, FORWARD, CURVE);

    // Create the IMM 3Y Outright Swap
    date effectiveDate3(2017, Dec, 10);
    date terminationDate3(2020, Dec, 10);
    string imm3Y = "MAC-Outright-3Y";
    IRSwap imm3YSwap(imm3Y, ACT_THREE_SIXTY, ACT_THREE_SIXTY, QUARTERLY, EURIBOR, TENOR_6M, effectiveDate3, terminationDate3, EUR, 3, MAC, OUTRIGHT);

    // Create a IRSwapProductService
    IRSwapProductService swapProductService;

    // Add the Spot 10Y Outright Swap to the IRSwapProductService and retrieve it from the service
    swapProductService.Add(outright10YSwap);
    IRSwap swap = swapProductService.GetData(outright10Y);
    // cout << "Swap: " << swap.GetProductId() << " ==> " << swap << endl;

    // Add the IMM 2Y Outright Swap to the IRSwapProductService and retrieve it from the service
    swapProductService.Add(imm2YSwap);
    swap = swapProductService.GetData(imm2Y);
    // cout << "Swap: " << swap.GetProductId() << " ==> " << swap << endl;

    swapProductService.Add(imm3YSwap);

    // Test utility methods on the IRSwapProductService
    cout << "\nTest utility methods on the IRSwapProductService below:\n";

    // Get all Swaps with the 30/360 fixed leg day count convention
    cout << "\nGet all Swaps with the 30/360 fixed leg day count convention\n";
    auto res = swapProductService.GetSwaps(THIRTY_THREE_SIXTY);
    for (const auto& b : res) {
        cout << b << "\n";
    }

    // Get all Swaps with SEMI-ANNUAL fixed leg payment frequency
    cout << "\nGet all Swaps with SEMI-ANNUAL fixed leg payment frequency\n";
    auto res1 = swapProductService.GetSwaps(SEMI_ANNUAL);
    for (const auto& b : res1) {
        cout << b << "\n";
    }

    // Get all Swaps with LIBOR floating index
    cout << "\nGet all Swaps with LIBOR floating index\n";
    res1 = swapProductService.GetSwaps(LIBOR);
    for (const auto& b : res1) {
        cout << b << "\n";
    }

    // Get all Swaps with a term in years greater than 3
    cout << "\nGet all Swaps with a term in years greater than 3\n";
    res1 = swapProductService.GetSwapsGreaterThan(3);
    for (const auto& b : res1) {
        cout << b << "\n";
    }

    // Get all Swaps with a term in years less than 3
    cout << "\nGet all Swaps with a term in years less than 3\n";
    res1 = swapProductService.GetSwapsLessThan(3);
    for (const auto& b : res1) {
        cout << b << "\n";
    }

    // Get all Swaps with the specified swap type (e.g., FORWARD)
    cout << "\nGet all Swaps with the specified swap type (e.g., FORWARD)\n";
    res1 = swapProductService.GetSwaps(FORWARD);
    for (const auto& b : res1) {
        cout << b << "\n";
    }

    // Get all Swaps with the specified swap leg type (e.g., OUTRIGHT)
    cout << "\nGet all Swaps with the specified swap leg type (e.g., OUTRIGHT)\n";
    res1 = swapProductService.GetSwaps(OUTRIGHT);
    for (const auto& b : res1) {
        cout << b << "\n";
    }
}

int main() {
    // Q2
    TestFutureProductService();
    // Q3
    TestBondProductService();
    TestIRswapProductService();
    return 0;
}


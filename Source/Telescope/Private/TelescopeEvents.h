// Copyright 2022 Telescope Labs, Inc. All Rights Reserved.

#pragma once
#include "Interfaces/IAnalyticsProvider.h"
#include "Http.h"
#include "DateTime.h"

/**
 * Telescope Labs Unreal Engine Analytics Provider plugin.
 * This SDK don't use local buffer, events are immediately uploaded.
 */
class TelescopeEvents :
  public IAnalyticsProvider
{
private:

    //= null, string segmentvalues = null, int? tester = null)


    FString abtestvalues;
    FString ad_network;
    FString ad_placement;
    FString ad_source;
    FString ad_unit;
    int32 amount;
    FString appversion;
    int32 appversionid;

    int32 cheater;
    FString county;
    FDateTime created;
    int32 currencytype;

    FString device;
    int32 deviceid;
    int32 difficalty;
    int32 duration;

    int32 eventlevel;
    FDateTime eventtime_daily;

    string firstappversion;
    int32 firstappversionid;
    FDateTime firstpaymentdate;

    FString item;
    FString itemtype;

    FDateTime lastpaymentdate;
    int32 level;
    FString locale;
    FString location;
    int32 locationid;
    int32 locationsource;

    FString osversion;
    int32 osversionid;

    int32 p1;
    int32 p21;
    int32 paying_status;
    int32 paymentcount;
    FString paymentid;
    double paymentsum;
    Fstring period;
    double price;
    double priceusd;
    int32 product;

    double revenue;

    FDateTime sbsfirstpaymentdate;
    int32 sbspaymentcount;
    double sbspaymentsum;
    FString sbs_state;
    FString sdkversion;
    int32 sdkversionid;
    FString segmentvalues;
    int32 success;
    int32 step;

    int32 tag_id;
    int32 tester;
    int32 valid

public:

    /* AdImpressions shows RoR of Ads    */
    /**
     * @param abtestvalues
     * @param ad_network
     * @param ad_placement
     * @param ad_source
     * @param ad_unit
     * @param appversion
     * @param appversionid
     * @param cheater
     * @param country
     * @param created
     * @param device
     * @param deviceid
     * @param eventlevel
     * @param firstappversion
     * @param firstappversionid
     * @param firstpaymentdate
     * @param lastpaymentdate
     * @param level
     * @param locale
     * @param location
     * @param locationid
     * @param osversion
     * @param osversionid
     * @param paymentcount
     * @param paymentsum
     * @param revenue
     * @param sbsfirstpaymentdate
     * @param sbspaymentcount
     * @param sbspaymentsum
     * @param sdkversion
     * @param sdkversionid
     * @param segmentvalues
     * @param tester
     */
    virtual void AdImpressions(
    const FString& abtestvalues = TEXT(""),
    const FString& ad_network = TEXT(""),
    const FString& ad_placement = TEXT(""),
    const FString& ad_source = TEXT(""),
    const FString& ad_unit = TEXT(""),
    const FString& appversion = TEXT(""),
    const int32& appversionid = 0,
    const int32& cheater = 0,
    const FString& country  = TEXT(""),
    const FDateTime& created = FDateTime(),
    const FString& device = TEXT(""),
    const int32& deviceid = 0,
    const int32& eventlevel = 0,
    const FString& firstappversion = TEXT(""),
    const int32& firstappversionid = 0,
    const FDateTime& firstpaymentdate = FDateTime(),
    const FDateTime& lastpaymentdate = FDateTime(),
    const int32& level = 0,
    const FString& locale = TEXT(""),
    const FString& location = TEXT(""),
    const int32& locationid = 0,
    const FString& osversion = TEXT(""),
    const int32& osversionid = 0,
    const int32& paymentcount = 0,
    const double paymentsum = 0.0,
    const double revenue = 0.0,
    const FDateTime& sbsfirstpaymentdate = FDateTime(),
    const int32& sbspaymentcount = 0,
    const double sbspaymentsum = 0.0,
    const FString& sdkversion = TEXT(""),
    const int32& sdkversionid = 0,
    const FString& segmentvalues = TEXT(""),
    const int32& tester = 0
    ) override;



    /* IngamePurchases shows RoR of Ads    */
    /**
     * @param amount
     * @param appversionid
     * @param cheater
     * @param country
     * @param currency
     * @param deviceid
     * @param firstappversionid
     * @param item
     * @param itemtype
     * @param level
     * @param locale
     * @param location
     * @param osversionid
     * @param p1
     * @param paying_status
     * @param paymentcount
     * @param paymentsum
     * @param price
     * @param sbspaymentcount
     * @param sbspaymentsum
     * @param tester
     */
    virtual void IngamePurchases(
    const int32& amount = 0,
    const int32& appversionid = 0,
    const int32& cheater = 0,
    const FString& country  = TEXT(""),
    const FString& currency  = TEXT(""),
    const FString& item  = TEXT(""),
    const FString& itemtype  = TEXT(""),
    const int32& deviceid = 0,
    const int32& firstappversionid = 0,
    const int32& level = 0,
    const FString& locale = TEXT(""),
    const int32& osversionid = 0,
    const int32& p1 = 0,
    const int32& paying_status = 0,
    const int32& paymentcount = 0,
    const double paymentsum = 0.0,
    const double price = 0.0,
    const int32& sbspaymentcount = 0,
    const double sbspaymentsum = 0.0,
    const int32& tester = 0) override;
   
   
    /* LevelUps     */
    /**
     * @param appversionid
     * @param cheater
     * @param country
     * @param deviceid
     * @param eventlevel
     * @param firstappversionid
     * @param level
     * @param locale
     * @param osversionid
     * @param paying_status
     * @param paymentcount
     * @param paymentsum
     * @param sbspaymentcount
     * @param sbspaymentsum
     * @param tester
     */
    
    virtual void LevelUps(
    const int32& appversionid = 0,
    const int32& cheater = 0,
    const FString& country  = TEXT(""),
    const int32& deviceid = 0,
    const int32& eventlevel = 0,
    const int32& firstappversionid = 0,
    const int32& level = 0,
    const FString& locale = TEXT(""),
    const int32& osversionid = 0,
    const int32& paying_status = 0,
    const int32& paymentcount = 0,
    const double paymentsum = 0.0,
    const int32& sbspaymentcount = 0,
    const double sbspaymentsum = 0.0,
    const int32& tester = 0
    ) override;

    /* LevelUpsCurrencies  */
    /**
     * @param appversionid
     * @param cheater
     * @param country
     * @param currencytype
     * @param deviceid
     * @param firstappversionid
     * @param level
     * @param locale
     * @param osversionid
     * @param p1
     * @param paying_status
     * @param paymentcount
     * @param paymentsum
     * @param price
     * @param sbspaymentcount
     * @param sbspaymentsum
     * @param tester
     */
    virtual void LevelUpsCurrencies( 
    const int32& appversionid = 0,
    const int32& cheater = 0,
    const FString& country  = TEXT(""),
    const int32& currencytype = 0,
    const int32& deviceid = 0,
    const int32& firstappversionid = 0,
    const int32& level = 0,
    const FString& locale = TEXT(""),
    const int32& p1 = 0,
    const int32& paying_status = 0,
    const int32& paymentcount = 0,
    const double paymentsum = 0.0,
    const double price = 0.0,
    const int32& sbspaymentcount = 0,
    const double sbspaymentsum = 0.0,
    const int32& tester = 0) override;

    /* Payments  */
    /**
     * @param appversionid
     * @param cheater
     * @param country
     * @param currencytype
     * @param deviceid
     * @param firstappversionid
     * @param level
     * @param locale
     * @param osversionid
     * @param paymentcount
     * @param paymentid
     * @param paymentsum
     * @param price
     * @param priceusd
     * @param product
     * @param sbspaymentcount
     * @param sbspaymentsum
     * @param tester
     * @param valid
     */
    virtual void Payments( 
    const int32& appversionid = 0,
    const int32& cheater = 0,
    const FString& country  = TEXT(""),
    const int32& currencytype = 0,
    const int32& deviceid = 0,
    const int32& firstappversionid = 0,
    const int32& level = 0,
    const FString& locale = TEXT(""),
    const int32& osversionid = 0,
    const FString& paymentid = 0,
    const int32& paymentcount = 0,
    const double paymentsum = 0.0,
    const double price = 0.0,
    const double priceusd = 0.0,
    const int32& product = 0,
    const int32& sbspaymentcount = 0,
    const double sbspaymentsum = 0.0,
    const int32& tester = 0,
    const int32& valid = 0
    ) override;

    /* AdImpressions shows RoR of Ads */
    /**
     * @param appversionid
     * @param cheater
     * @param country
     * @param currencytype
     * @param deviceid
     * @param difficalty
     * @param duration
     * @param firstappversionid
     * @param level
     * @param locale
     * @param locationid
     * @param locationsource
     * @param osversionid
     * @param paying_status
     * @param paymentcount
     * @param paymentsum
     * @param sbspaymentcount
     * @param sbspaymentsum
     * @param success
     * @param tester
     */
    virtual void Progressions( 
    const int32& appversionid = 0,
    const int32& cheater = 0,
    const FString& country  = TEXT(""),
    const int32& currencytype = 0,
    const int32& deviceid = 0,
    const int32& difficalty = 0,
    const int32& duration = 0,
    const int32& firstappversionid = 0,
    const int32& level = 0,
    const FString& locale = TEXT(""),
    const int32& locationid = 0,
    const int32& locationsource = 0,
    const int32& osversionid = 0,
    const int32& paying_status = 0,
    const int32& paymentcount = 0,
    const double paymentsum = 0.0,
    const int32& sbspaymentcount = 0,
    const double sbspaymentsum = 0.0,
    const int32& success = 0,
    const int32& tester = 0) override;


    /* PushSent shows RoR of Ads    */
    /**
     * @param appversionid
     * @param cheater
     * @param country
     * @param deviceid
     * @param firstappversionid
     * @param level
     * @param locale
     * @param osversionid
     * @param paying_status
     * @param paymentcount
     * @param paymentsum
     * @param sbspaymentcount
     * @param sbspaymentsum
     * @param tag_id
     * @param tester
     */
    virtual void PushSent( 
    const int32& appversionid = 0,
    const int32& cheater = 0,
    const FString& country  = TEXT(""),
    const int32& deviceid = 0,
    const int32& firstappversionid = 0,
    const int32& level = 0,
    const FString& locale = TEXT(""),
    const int32& osversionid = 0,
    const int32& paying_status = 0,
    const int32& paymentcount = 0,
    const double paymentsum = 0.0,
    const int32& sbspaymentcount = 0,
    const double sbspaymentsum = 0.0,
    const int32& tag_id = 0,
    const int32& tester = 0) override;




        /* Subscriptions shows RoR of Ads
        */
    /**
     * @param appversionid
     * @param cheater
     * @param country
     * @param currency
     * @param deviceid
     * @param firstappversionid
     * @param level
     * @param locale
     * @param osversionid
     * @param p21
     * @param paymentcount
     * @param paymentsum
     * @param period
     * @param price
     * @param priceusd
     * @param product
     * @param sbspaymentcount
     * @param sbspaymentsum
     * @param tester
     * @param valid
     */
    virtual void Subscriptions(
    const int32& appversionid = 0,
    const int32& cheater = 0,
    const FString& country  = TEXT(""),
    const FString& currency  = TEXT(""),
    const int32& deviceid = 0,
    const int32& firstappversionid = 0,
    const int32& level = 0,
    const FString& locale = TEXT(""),
    const int32& osversionid = 0,
    const int32& p21 = 0,
    const int32& paymentcount = 0,
    const double paymentsum = 0.0,
    const FString& period = TEXT(""),
    const double price = 0.0,
    const double priceusd = 0.0,
    const int32& product = 0,
    const FString& sbs_state = TEXT(""),
    const int32& sbspaymentcount = 0,
    const double sbspaymentsum = 0.0,
    const int32& tester = 0,
    const int32& valid = 0) override;

        /* Tutorials shows RoR of Ads
        */
    /**
     * @param appversionid
     * @param cheater
     * @param country
     * @param deviceid
     * @param eventtime_daily
     * @param firstappversionid
     * @param level
     * @param locale
     * @param osversionid
     * @param paying_status
     * @param paymentcount
     * @param paymentsum
     * @param sbspaymentcount
     * @param sbspaymentsum
     * @param step
     * @param tester
     */
    virtual void Tutorials(
    const int32& appversionid = 0,
    const int32& cheater = 0,
    const FString& country  = TEXT(""),
    const int32& deviceid = 0,
    const FDateTime& eventtime_daily  = FDateTime(),
    const int32& firstappversionid = 0,
    const int32& level = 0,
    const FString& locale = TEXT(""),
    const int32& osversionid = 0,
    const int32& paying_status = 0,
    const int32& paymentcount = 0,
    const double paymentsum = 0.0,
    const int32& sbspaymentcount = 0,
    const double sbspaymentsum = 0.0,
    const int32& step = 0,
    const int32& tester = 0) override;



};
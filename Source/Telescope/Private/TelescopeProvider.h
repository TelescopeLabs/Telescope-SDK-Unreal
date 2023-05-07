// Copyright 2022 Telescope Labs, Inc. All Rights Reserved.

#pragma once
#include "Interfaces/IAnalyticsProvider.h"
#include "Http.h"

/**
 * Telescope Labs Unreal Engine Analytics Provider plugin.
 * This SDK don't use local buffer, events are immediately uploaded.
 */
class FAnalyticsProviderTelescope :
  public IAnalyticsProvider
{
private:

    FString ApiKey;

    /// Tracks whether we need to start the session or restart it 
    bool bHasSessionStarted;

    /// Whether an event was written before or not
    bool bHasWrittenFirstEvent;

    /// Id representing the user the analytics are recording for
    FString UserId;

    /// Unique Id representing the session the analytics are recording for 
    FString SessionId;

    /// Holds the Age if set 
    int32 Age;

    /// Holds the Location of the user if set 
    FString Location;

    /// Holds the Gender of the user if set 
    FString Gender;

    /// Holds the build info if set 
    FString BuildInfo;

    /// Events associated when StartSession and EndSession are triggered 
    TArray<FAnalyticsEventAttribute> EventAttributes;

    static TSharedPtr<IAnalyticsProvider> Provider;
    FAnalyticsProviderTelescope(const FString Key);

public:
  /** 
   * All events will be recorded to two tables, `Sessions` and `Events`. 
   * @param Key Write only API Key
   * @return TD Analytics Provider Instance
   */
  static TSharedPtr<IAnalyticsProvider> Create(const FString Key)
    {
      if (!Provider.IsValid()){
        Provider = TSharedPtr<IAnalyticsProvider>(new FAnalyticsProviderTelescope(Key));
      }
      return Provider;
    }

  /**
   * Remove all configuration data from the Treasure Data instance. 
   */
  static void Destroy(){
    Provider.Reset();
  }

  static TSharedPtr<FAnalyticsProviderTelescope> GetProvider() {
    return StaticCastSharedPtr<FAnalyticsProviderTelescope>(Provider);
  }

    virtual ~FAnalyticsProviderTelescope();

    /**
     * Start the session
     * @param Attributes Additional event attributes
     * @return bool true if session started successfully
     */
    virtual bool StartSession(const TArray<FAnalyticsEventAttribute>& Attributes) override;
    
    /**
     * End the session
     */
    virtual void EndSession() override;
    
    virtual void FlushEvents() override;

    /**
     * Set the ID of the User
     * @param InUserID String representing the User ID. Preferably Unique.
     */
    virtual void SetUserID(const FString& InUserID) override;
    
    /**
     * Get the ID of the User
     * @return FString string representing the User ID
     */
    virtual FString GetUserID() const override;

    /**
     * Get the current session ID
     * @return FString string representing the current session ID
     */
    virtual FString GetSessionID() const override;
    
    /**
     * Set the Session ID of the User
     * @param InSessionID session id as a string
     * @return bool true if session id set successfully
     */
    virtual bool SetSessionID(const FString& InSessionID) override;

    /**
     * Record an event
     * @param EventName Name of Event
     * @param Attributes Attributes as an array
     */
    virtual void RecordEvent(const FString& EventName, const TArray<FAnalyticsEventAttribute>& Attributes) override;

    
    /**
     * Record an item purchase
     * @param ItemId string representing ID of item
     * @param Currency string representing ID of currency
     * @param PerItemCost integer cost of item
     * @param ItemQuantity number of items
     */
    virtual void RecordItemPurchase(const FString& ItemId, const FString& Currency, int PerItemCost, int ItemQuantity) override;

    /**
     * Record purchse of currency
     * @param GameCurrencyType Type of currency as a string
     * @param GameCurrencyAmount Amount of currency as a integer
     * @param RealCurrencyType Currency type as a string
     * @param RealMoneyCost Cost in Real dollas as a float
     * @param PaymentProvider Payment Provider as a string
     */
    virtual void RecordCurrencyPurchase(const FString& GameCurrencyType, int GameCurrencyAmount, const FString& RealCurrencyType, float RealMoneyCost, const FString& PaymentProvider) override;

    /**
     * Record the currency given to the user
     * @param GameCurrencyType Type of in-game currency as a string
     * @param GameCurrencyAmount Amount of in-game currency as an integer
     */
    virtual void RecordCurrencyGiven(const FString& GameCurrencyType, int GameCurrencyAmount) override;

    /**
     * Set the build information
     * @param InBuildInfo Build information as a string
     */
    virtual void SetBuildInfo(const FString& InBuildInfo) override;
    
    /**
     * Set the Gender of the User
     * @param InGender String representing the gender
     */
    virtual void SetGender(const FString& InGender) override;
    
    /**
     * Set the Location of the User
     * @param InLocation String representing the location of the user
     */
    virtual void SetLocation(const FString& InLocation) override;
    
    /**
     * Set the Age of the User
     * @param InAge Integer representing the age of the user
     */
    virtual void SetAge(const int32 InAge) override;

    /**
     * Record the purchase of an in-game item
     * @param ItemId ID of the item as a string
     * @param ItemQuantity Number of items as an integer
     * @param EventAttrs Additional event attributes
     */
    virtual void RecordItemPurchase(const FString& ItemId, int ItemQuantity, const TArray<FAnalyticsEventAttribute>& EventAttrs) override;
    
    /**
     * Record purchase of in-game currency
     * @param GameCurrencyType Type of currency in game as a string
     * @param GameCurrencyAmount Amount of currency as an integer
     * @param EventAttrs Additional event attributes
     */
    virtual void RecordCurrencyPurchase(const FString& GameCurrencyType, int GameCurrencyAmount, const TArray<FAnalyticsEventAttribute>& EventAttrs) override;
    
    /**
     * Record currency given to user in-game
     * @param GameCurrencyType Type of currency
     * @param GameCurrencyAmount Amount of currency
     * @param EventAttrs Additional event attributes
     */
    virtual void RecordCurrencyGiven(const FString& GameCurrencyType, int GameCurrencyAmount, const TArray<FAnalyticsEventAttribute>& EventAttrs) override;
    
    /**
     * When things go wrong, record an error
     * @param Error Error event name
     * @param EventAttrs Error event attributes
     */
    virtual void RecordError(const FString& Error, const TArray<FAnalyticsEventAttribute>& EventAttrs) override;
    
    /**
     * Record progress of user
     * @param ProgressType Type of progress as a string
     * @param ProgressHierarchy Hierarchy of progress as a string
     * @param EventAttrs Additional event attributes
     */
    virtual void RecordProgress(const FString& ProgressType, const FString& ProgressHierarchy, const TArray<FAnalyticsEventAttribute>& EventAttrs) override;
    
    void EventRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);

    /**
     * Add basic event with value
     * @param EventName Name of Event
     * @param EventValue Value of event
     */
    void AddEventAttribute(const FString& EventName, const FString& EventValue);
    
    /**
     * Clear event attributes
     */
    void ClearEventAttributes();


  /**
   * Convenience function to transform API Endpoint enumerations into postback API address string.
   * @return string with the postback api endpoint
   */
  inline FString GetAPIURL()
  {
    return TEXT("https://api.telescopelabs.io/api/eventrouter?apikey=");
  }
};
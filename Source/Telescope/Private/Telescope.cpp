// Copyright 2017 Treasure Data, Inc. All Rights Reserved.

#include "Telescope.h"
#include "TelescopePrivate.h"
#include "TelescopeEvents.h"
#include "Http.h"
#include "DateTime.h"
#include <string>

DEFINE_LOG_CATEGORY_STATIC(LogAnalytics, Display, All);
IMPLEMENT_MODULE(FAnalyticsTelescope, Telescope)

TSharedPtr<IAnalyticsProvider> FAnalyticsProviderTelescope::Provider;

void FAnalyticsTelescope::StartupModule()
{
}

void FAnalyticsTelescope::ShutdownModule()
{
    FAnalyticsProviderTelescope::Destroy();
}

TSharedPtr<IAnalyticsProvider> FAnalyticsTelescope::CreateAnalyticsProvider(const FAnalyticsProviderConfigurationDelegate &GetConfigValue) const
{
    if (GetConfigValue.IsBound())
    {
        const FString Key = GetConfigValue.Execute(TEXT("TDApiKey"), true);
    }

}

// Provider
FAnalyticsProviderTelescope::FAnalyticsProviderTelescope(const FString Key, const FString DBName, FAnalyticsRegion ERegion) : ApiKey(Key),Database(DBName),Region(ERegion),(false)
{
    // Require TD to add IP field
    AddEventAttribute("td_ip", "td_ip");
    AddEventAttribute("td_locale_lang", FPlatformMisc::GetDefaultLanguage());
    AddEventAttribute("td_locale_country", FPlatformMisc::GetDefaultLocale());
}

FAnalyticsProviderTelescope::~FAnalyticsProviderTelescope()
{
    if (bHasSessionStarted)
    {
        EndSession();
    }
}

void TelescopeEvents::AdImpressions(
    const FString &abtestvalues,
    const FString &ad_network,
    const FString &ad_placement,
    const FString &ad_source,
    const FString &ad_unit,
    const FString &appversion,
    const int32 &appversionid,
    const int32 &cheater,
    const FString &country,
    const FDateTime &created,
    const FString &device,
    const int32 &deviceid,
    const int32 &eventlevel,
    const FString &firstappversion,
    const int32 &firstappversionid,
    const FDateTime &firstpaymentdate,
    const FDateTime &lastpaymentdate,
    const int32 &level,
    const FString &locale,
    const FString &location,
    const int32 &locationid,
    const FString &osversion,
    const int32 &osversionid,
    const int32 &paymentcount,
    const double &paymentsum,
    const double &revenue,
    const FDateTime &sbsfirstpaymentdate,
    const int32 &sbspaymentcount,
    const double &sbspaymentsum,
    const FString &sdkversion,
    const int32 &sdkversionid,
    const FString &segmentvalues,
    const int32 &tester)
{

    const FDateTime created = FDateTime::Now()

    TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);

    JsonObject->SetStringField("entityName", "AdImpressions");
    JsonObject->SetStringField("type", "insert");
    JsonObject->SetStringField("id", "playerIdHere");

    TSharedPtr<FJsonObject> JsonValue = MakeShareable(new FJsonObject);

    JsonValue->SetStringField("abtestvalues", abtestvalues);
    JsonValue->SetStringField("ad_network", ad_network);
    JsonValue->SetStringField("ad_placement", ad_placement);
    JsonValue->SetStringField("ad_source", ad_source);
    JsonValue->SetStringField("ad_unit", ad_unit);
    JsonValue->SetStringField("appversion", appversion);
    JsonValue->SetNumberField("appversionid", appversionid);
    JsonValue->SetNumberField("cheater", cheater);
    JsonValue->SetStringField("country", country);
    JsonValue->SetStringField("created", created.ToString());
    JsonValue->SetStringField("device", device);
    JsonValue->SetNumberField("deviceid", deviceid);
    JsonValue->SetNumberField("eventlevel", eventlevel);
    JsonValue->SetStringField("firstappversion", firstappversion);
    JsonValue->SetNumberField("firstappversionid", firstappversionid);
    JsonValue->SetStringField("firstpaymentdate", firstpaymentdate.ToString());
    JsonValue->SetStringField("lastpaymentdate", lastpaymentdate.ToString());
    JsonValue->SetNumberField("level", level);
    JsonValue->SetStringField("locale", locale);
    JsonValue->SetStringField("location", location);
    JsonValue->SetNumberField("locationid", locationid);
    JsonValue->SetStringField("osversion", osversion);
    JsonValue->SetNumberField("osversionid", osversionid);
    JsonValue->SetNumberField("paymentcount", paymentcount);
    JsonValue->SetNumberField("paymentsum", paymentsum);
    JsonValue->SetNumberField("revenue", revenue);
    JsonValue->SetStringField("sbsfirstpaymentdate", sbsfirstpaymentdate.ToString());
    JsonValue->SetNumberField("sbspaymentcount", sbspaymentcount);
    JsonValue->SetNumberField("sbspaymentsum", sbspaymentsum);
    JsonValue->SetStringField("sdkversion", sdkversion);
    JsonValue->SetNumberField("sdkversionid", sdkversionid);
    JsonValue->SetStringField("segmentvalues", segmentvalues);
    JsonValue->SetNumberField("tester", tester);

    JsonObject->SetObjectField("value", JsonValue);

    FJsonSerializer::Serialize(JsonObject.ToSharedRef(), JsonWriter);
    FString JsonString;
    TSharedRef<TJsonWriter<>> JsonWriter = TJsonWriterFactory<>::Create(&JsonString);

    // HTTP Request
    const FString Apikey = GetConfigValue.Execute(TEXT("TelescopeApikey"), true);

    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest = FHttpModule::Get().CreateRequest();
    HttpRequest->SetVerb("POST");
    HttpRequest->SetHeader("Content-Type", "application/json");
    HttpRequest->SetURL(GetAPIURL() + Apikey);
    HttpRequest->SetContentAsString(JsonString);

    HttpRequest->OnProcessRequestComplete().BindRaw(this, &FAnalyticsProviderTelescope::EventRequestComplete);
    HttpRequest->ProcessRequest();

}






void TelescopeEvents::IngamePurchases(
    const int32& amount,
    const int32 &appversionid,
    const int32 &cheater,
    const FString &country,
    const FString &currency,
    const FString &item,
    const FString &itemtype,
    const int32 &deviceid,
    const int32 &firstappversionid,
    const int32 &level,
    const FString &locale,
    const int32 &osversionid,
    const int32 &p1,
    const int32 &paying_status,
    const int32 &paymentcount,
    const double &paymentsum,
    const double &price,
    const int32 &sbspaymentcount,
    const double &sbspaymentsum,
    const int32 &tester)
{

    FDateTime created = FDateTime::Now()

    TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
    
    JsonObject->SetStringField("entityName", "IngamePurchases");
    JsonObject->SetStringField("type", "insert");
    JsonObject->SetStringField("id", "playerIdHere");

    TSharedPtr<FJsonObject> JsonValue = MakeShareable(new FJsonObject);

    JsonValue->SetNumberField("amount", amount);
    JsonValue->SetNumberField("appversionid", appversionid);
    JsonValue->SetNumberField("cheater", cheater);
    JsonValue->SetStringField("country", country);
    JsonValue->SetStringField("currency", currency);
    JsonValue->SetStringField("item", item);
    JsonValue->SetStringField("itemtype", itemtype);
    JsonValue->SetNumberField("deviceid", deviceid);
    JsonValue->SetNumberField("firstappversionid", firstappversionid);
    JsonValue->SetNumberField("level", level);
    JsonValue->SetStringField("locale", locale);
    JsonValue->SetNumberField("osversionid", osversionid);
    JsonValue->SetNumberField("p1", p1);
    JsonValue->SetNumberField("paying_status", paying_status);
    JsonValue->SetNumberField("paymentcount", paymentcount);
    JsonValue->SetNumberField("paymentsum", paymentsum);
    JsonValue->SetNumberField("price", price);
    JsonValue->SetNumberField("sbspaymentcount", sbspaymentcount);
    JsonValue->SetNumberField("sbspaymentsum", sbspaymentsum);
    JsonValue->SetNumberField("tester", tester);

    JsonObject->SetObjectField("value", JsonValue);

    FJsonSerializer::Serialize(JsonObject.ToSharedRef(), JsonWriter);
    FString JsonString;
    TSharedRef<TJsonWriter<>> JsonWriter = TJsonWriterFactory<>::Create(&JsonString);

    // HTTP Request
    const FString Apikey = GetConfigValue.Execute(TEXT("TelescopeApikey"), true);

    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest = FHttpModule::Get().CreateRequest();
    HttpRequest->SetVerb("POST");
    HttpRequest->SetHeader("Content-Type", "application/json");
    HttpRequest->SetURL(GetAPIURL() + Apikey);
    HttpRequest->SetContentAsString(JsonString);

    HttpRequest->OnProcessRequestComplete().BindRaw(this, &FAnalyticsProviderTelescope::EventRequestComplete);
    HttpRequest->ProcessRequest();

}






void TelescopeEvents::LevelUps(
    const int32 &appversionid,
    const int32 &cheater,
    const FString &country,
    const int32 &deviceid,
    const int32 &eventlevel,
    const int32 &firstappversionid,
    const int32 &level,
    const FString &locale,
    const int32 &osversionid,
    const int32 &paying_status,
    const int32 &paymentcount,
    const double &paymentsum,
    const int32 &sbspaymentcount,
    const double &sbspaymentsum,
    const int32 &tester)
{

    FDateTime created = FDateTime::Now()

    TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
    
    JsonObject->SetStringField("entityName", "IngamePurchases");
    JsonObject->SetStringField("type", "insert");
    JsonObject->SetStringField("id", "playerIdHere");

    TSharedPtr<FJsonObject> JsonValue = MakeShareable(new FJsonObject);


    JsonValue->SetNumberField("appversionid", appversionid);
    JsonValue->SetNumberField("cheater", cheater);
    JsonValue->SetStringField("country", country);
    JsonValue->SetNumberField("deviceid", deviceid);
    JsonValue->SetNumberField("eventlevel", eventlevel);
    JsonValue->SetNumberField("firstappversionid", firstappversionid);
    JsonValue->SetNumberField("level", level);
    JsonValue->SetStringField("locale", locale);
    JsonValue->SetNumberField("osversionid", osversionid);
    JsonValue->SetNumberField("paying_status", paying_status);
    JsonValue->SetNumberField("paymentcount", paymentcount);
    JsonValue->SetNumberField("paymentsum", paymentsum);
    JsonValue->SetNumberField("sbspaymentcount", sbspaymentcount);
    JsonValue->SetNumberField("sbspaymentsum", sbspaymentsum);
    JsonValue->SetNumberField("tester", tester);

    JsonObject->SetObjectField("value", JsonValue);

    FJsonSerializer::Serialize(JsonObject.ToSharedRef(), JsonWriter);
    FString JsonString;
    TSharedRef<TJsonWriter<>> JsonWriter = TJsonWriterFactory<>::Create(&JsonString);

    // HTTP Request
    const FString Apikey = GetConfigValue.Execute(TEXT("TelescopeApikey"), true);

    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest = FHttpModule::Get().CreateRequest();
    HttpRequest->SetVerb("POST");
    HttpRequest->SetHeader("Content-Type", "application/json");
    HttpRequest->SetURL(GetAPIURL() + Apikey);
    HttpRequest->SetContentAsString(JsonString);

    HttpRequest->OnProcessRequestComplete().BindRaw(this, &FAnalyticsProviderTelescope::EventRequestComplete);
    HttpRequest->ProcessRequest();

}





void TelescopeEvents::LevelUpsCurrencies(
    const int32 &appversionid,
    const int32 &cheater,
    const FString &country,
    const int32 &currencytype,
    const int32 &deviceid,
    const int32 &firstappversionid,
    const int32 &level,
    const FString &locale,
    const int32 &p1,
    const int32 &paying_status,
    const int32 &paymentcount,
    const double &paymentsum,
    const int32 &price,
    const int32 &sbspaymentcount,
    const double &sbspaymentsum,
    const int32 &tester)
{

    FDateTime created = FDateTime::Now()

    TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
    
    JsonObject->SetStringField("entityName", "IngamePurchases");
    JsonObject->SetStringField("type", "insert");
    JsonObject->SetStringField("id", "playerIdHere");

    TSharedPtr<FJsonObject> JsonValue = MakeShareable(new FJsonObject);


    JsonValue->SetNumberField("appversionid", appversionid);
    JsonValue->SetNumberField("cheater", cheater);
    JsonValue->SetStringField("country", country);
    JsonValue->SetNumberField("currencytype", currencytype);
    JsonValue->SetNumberField("deviceid", deviceid);
    JsonValue->SetNumberField("firstappversionid", firstappversionid);
    JsonValue->SetNumberField("level", level);
    JsonValue->SetStringField("locale", locale);
    JsonValue->SetNumberField("p1", p1);
    JsonValue->SetNumberField("paying_status", paying_status);
    JsonValue->SetNumberField("paymentcount", paymentcount);
    JsonValue->SetNumberField("paymentsum", paymentsum);
    JsonValue->SetNumberField("price", price);
    JsonValue->SetNumberField("sbspaymentcount", sbspaymentcount);
    JsonValue->SetNumberField("sbspaymentsum", sbspaymentsum);
    JsonValue->SetNumberField("tester", tester);

    JsonObject->SetObjectField("value", JsonValue);

    FJsonSerializer::Serialize(JsonObject.ToSharedRef(), JsonWriter);
    FString JsonString;
    TSharedRef<TJsonWriter<>> JsonWriter = TJsonWriterFactory<>::Create(&JsonString);

    // HTTP Request
    const FString Apikey = GetConfigValue.Execute(TEXT("TelescopeApikey"), true);

    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest = FHttpModule::Get().CreateRequest();
    HttpRequest->SetVerb("POST");
    HttpRequest->SetHeader("Content-Type", "application/json");
    HttpRequest->SetURL(GetAPIURL() + Apikey);
    HttpRequest->SetContentAsString(JsonString);

    HttpRequest->OnProcessRequestComplete().BindRaw(this, &FAnalyticsProviderTelescope::EventRequestComplete);
    HttpRequest->ProcessRequest();

}


void TelescopeEvents::Payments(
    const int32 &appversionid,
    const int32 &cheater,
    const FString &country,
    const int32 &currencytype,
    const int32 &deviceid,
    const int32 &firstappversionid,
    const int32 &level,
    const FString &locale,
    const int32 &osversionid,
    const FString &paymentid,
    const int32 &paymentcount,
    const double &paymentsum,
    const int32 &price,
    const int32 &priceusd,
    const int32 &sbspaymentcount,
    const double &sbspaymentsum,
    const int32 &tester,
    const int32 &valid
    )
{

    FDateTime created = FDateTime::Now()

    TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
    
    JsonObject->SetStringField("entityName", "IngamePurchases");
    JsonObject->SetStringField("type", "insert");
    JsonObject->SetStringField("id", "playerIdHere");

    TSharedPtr<FJsonObject> JsonValue = MakeShareable(new FJsonObject);


    JsonValue->SetNumberField("appversionid", appversionid);
    JsonValue->SetNumberField("cheater", cheater);
    JsonValue->SetStringField("country", country);
    JsonValue->SetNumberField("currencytype", currencytype);
    JsonValue->SetNumberField("deviceid", deviceid);
    JsonValue->SetNumberField("firstappversionid", firstappversionid);
    JsonValue->SetNumberField("level", level);
    JsonValue->SetStringField("locale", locale);
    JsonValue->SetNumberField("osversionid", osversionid);
    JsonValue->SetStringField("paymentid", paymentid);
    JsonValue->SetNumberField("paymentcount", paymentcount);
    JsonValue->SetNumberField("paymentsum", paymentsum);
    JsonValue->SetNumberField("price", price);
    JsonValue->SetNumberField("priceusd", priceusd);
    JsonValue->SetNumberField("sbspaymentcount", sbspaymentcount);
    JsonValue->SetNumberField("sbspaymentsum", sbspaymentsum);
    JsonValue->SetNumberField("tester", tester);
    JsonValue->SetNumberField("valid", valid);

    JsonObject->SetObjectField("value", JsonValue);

    FJsonSerializer::Serialize(JsonObject.ToSharedRef(), JsonWriter);
    FString JsonString;
    TSharedRef<TJsonWriter<>> JsonWriter = TJsonWriterFactory<>::Create(&JsonString);

    // HTTP Request
    const FString Apikey = GetConfigValue.Execute(TEXT("TelescopeApikey"), true);

    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest = FHttpModule::Get().CreateRequest();
    HttpRequest->SetVerb("POST");
    HttpRequest->SetHeader("Content-Type", "application/json");
    HttpRequest->SetURL(GetAPIURL() + Apikey);
    HttpRequest->SetContentAsString(JsonString);

    HttpRequest->OnProcessRequestComplete().BindRaw(this, &FAnalyticsProviderTelescope::EventRequestComplete);
    HttpRequest->ProcessRequest();

}





void TelescopeEvents::Progressions(
    const int32 &appversionid,
    const int32 &cheater,
    const FString &country,
    const int32 &currencytype,
    const int32 &deviceid,
    const int32 &difficalty,
    const int32 &duration,
    const int32 &firstappversionid,
    const int32 &level,
    const FString &locale,
    const int32 &locationid,
    const int32 &locationsource,
    const int32 &osversionid,
    const int32 &paying_status,
    const int32 &paymentcount,
    const double &paymentsum,
    const int32 &sbspaymentcount,
    const double &sbspaymentsum,
    const int32 &success,
    const int32 &tester
    )
{

    FDateTime created = FDateTime::Now()

    TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
    
    JsonObject->SetStringField("entityName", "IngamePurchases");
    JsonObject->SetStringField("type", "insert");
    JsonObject->SetStringField("id", "playerIdHere");

    TSharedPtr<FJsonObject> JsonValue = MakeShareable(new FJsonObject);


    JsonValue->SetNumberField("appversionid", appversionid);
    JsonValue->SetNumberField("cheater", cheater);
    JsonValue->SetStringField("country", country);
    JsonValue->SetNumberField("currencytype", currencytype);
    JsonValue->SetNumberField("deviceid", deviceid);
    JsonValue->SetNumberField("difficalty", difficalty);
    JsonValue->SetNumberField("duration", duration);
    JsonValue->SetNumberField("firstappversionid", firstappversionid);
    JsonValue->SetNumberField("level", level);
    JsonValue->SetStringField("locale", locale);
    JsonValue->SetNumberField("locationid", locationid);
    JsonValue->SetNumberField("locationsource", locationsource);
    JsonValue->SetNumberField("osversionid", osversionid);
    JsonValue->SetNumberField("paying_status", paying_status);
    JsonValue->SetNumberField("paymentcount", paymentcount);
    JsonValue->SetNumberField("paymentsum", paymentsum);
    JsonValue->SetNumberField("sbspaymentcount", sbspaymentcount);
    JsonValue->SetNumberField("sbspaymentsum", sbspaymentsum);
    JsonValue->SetNumberField("success", success);
    JsonValue->SetNumberField("tester", tester);

    JsonObject->SetObjectField("value", JsonValue);

    FJsonSerializer::Serialize(JsonObject.ToSharedRef(), JsonWriter);
    FString JsonString;
    TSharedRef<TJsonWriter<>> JsonWriter = TJsonWriterFactory<>::Create(&JsonString);

    // HTTP Request
    const FString Apikey = GetConfigValue.Execute(TEXT("TelescopeApikey"), true);

    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest = FHttpModule::Get().CreateRequest();
    HttpRequest->SetVerb("POST");
    HttpRequest->SetHeader("Content-Type", "application/json");
    HttpRequest->SetURL(GetAPIURL() + Apikey);
    HttpRequest->SetContentAsString(JsonString);

    HttpRequest->OnProcessRequestComplete().BindRaw(this, &FAnalyticsProviderTelescope::EventRequestComplete);
    HttpRequest->ProcessRequest();

}




void TelescopeEvents::PushSent(
    const int32 &appversionid,
    const int32 &cheater,
    const FString &country,
    const int32 &deviceid,
    const int32 &firstappversionid,
    const int32 &level,
    const FString &locale,
    const int32 &osversionid,
    const int32 &paying_status,
    const int32 &paymentcount,
    const double &paymentsum,
    const int32 &sbspaymentcount,
    const double &sbspaymentsum,
    const int32 &tag_id,
    const int32 &tester)
{

    FDateTime created = FDateTime::Now()

    TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
    
    JsonObject->SetStringField("entityName", "IngamePurchases");
    JsonObject->SetStringField("type", "insert");
    JsonObject->SetStringField("id", "playerIdHere");

    TSharedPtr<FJsonObject> JsonValue = MakeShareable(new FJsonObject);


    JsonValue->SetNumberField("appversionid", appversionid);
    JsonValue->SetNumberField("cheater", cheater);
    JsonValue->SetStringField("country", country);
    JsonValue->SetNumberField("deviceid", deviceid);
    JsonValue->SetNumberField("firstappversionid", firstappversionid);
    JsonValue->SetNumberField("level", level);
    JsonValue->SetStringField("locale", locale);
    JsonValue->SetNumberField("osversionid", osversionid);
    JsonValue->SetNumberField("paying_status", paying_status);
    JsonValue->SetNumberField("paymentcount", paymentcount);
    JsonValue->SetNumberField("paymentsum", paymentsum);
    JsonValue->SetNumberField("sbspaymentcount", sbspaymentcount);
    JsonValue->SetNumberField("sbspaymentsum", sbspaymentsum);
    JsonValue->SetNumberField("tag_id", tag_id);
    JsonValue->SetNumberField("tester", tester);

    JsonObject->SetObjectField("value", JsonValue);

    FJsonSerializer::Serialize(JsonObject.ToSharedRef(), JsonWriter);
    FString JsonString;
    TSharedRef<TJsonWriter<>> JsonWriter = TJsonWriterFactory<>::Create(&JsonString);

    // HTTP Request
    const FString Apikey = GetConfigValue.Execute(TEXT("TelescopeApikey"), true);

    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest = FHttpModule::Get().CreateRequest();
    HttpRequest->SetVerb("POST");
    HttpRequest->SetHeader("Content-Type", "application/json");
    HttpRequest->SetURL(GetAPIURL() + Apikey);
    HttpRequest->SetContentAsString(JsonString);

    HttpRequest->OnProcessRequestComplete().BindRaw(this, &FAnalyticsProviderTelescope::EventRequestComplete);
    HttpRequest->ProcessRequest();

}






void TelescopeEvents::Subscriptions(
    const int32 &appversionid,
    const int32 &cheater,
    const FString &country,
    const FString &currency,
    const int32 &deviceid,
    const int32 &firstappversionid,
    const int32 &level,
    const FString &locale,
    const int32 &osversionid,
    const int32 &p21,
    const int32 &paymentcount,
    const double &paymentsum,
    const FString& period,
    const double price,
    const double priceusd,
    const int32& product,
    const FString& sbs_state,
    const int32 &sbspaymentcount,
    const double &sbspaymentsum,
    const int32 &tester,
    const int32 &valid
    )
{

    FDateTime created = FDateTime::Now()

    TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
    
    JsonObject->SetStringField("entityName", "IngamePurchases");
    JsonObject->SetStringField("type", "insert");
    JsonObject->SetStringField("id", "playerIdHere");

    TSharedPtr<FJsonObject> JsonValue = MakeShareable(new FJsonObject);


    JsonValue->SetNumberField("appversionid", appversionid);
    JsonValue->SetNumberField("cheater", cheater);
    JsonValue->SetStringField("country", country);
    JsonValue->SetStringField("currency", currency);
    JsonValue->SetNumberField("deviceid", deviceid);
    JsonValue->SetNumberField("firstappversionid", firstappversionid);
    JsonValue->SetNumberField("level", level);
    JsonValue->SetStringField("locale", locale);
    JsonValue->SetNumberField("osversionid", osversionid);
    JsonValue->SetNumberField("p21", p21);
    JsonValue->SetNumberField("paymentcount", paymentcount);
    JsonValue->SetNumberField("paymentsum", paymentsum);
    JsonValue->SetStringField("period", period);
    JsonValue->SetNumberField("price", price);
    JsonValue->SetNumberField("priceusd", priceusd);
    JsonValue->SetNumberField("product", product);
    JsonValue->SetStringField("sbs_state", sbs_state);
    JsonValue->SetNumberField("sbspaymentcount", sbspaymentcount);
    JsonValue->SetNumberField("sbspaymentsum", sbspaymentsum);
    JsonValue->SetNumberField("tester", tester);
    JsonValue->SetNumberField("valid", valid);

    JsonObject->SetObjectField("value", JsonValue);

    FJsonSerializer::Serialize(JsonObject.ToSharedRef(), JsonWriter);
    FString JsonString;
    TSharedRef<TJsonWriter<>> JsonWriter = TJsonWriterFactory<>::Create(&JsonString);

    // HTTP Request
    const FString Apikey = GetConfigValue.Execute(TEXT("TelescopeApikey"), true);

    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest = FHttpModule::Get().CreateRequest();
    HttpRequest->SetVerb("POST");
    HttpRequest->SetHeader("Content-Type", "application/json");
    HttpRequest->SetURL(GetAPIURL() + Apikey);
    HttpRequest->SetContentAsString(JsonString);

    HttpRequest->OnProcessRequestComplete().BindRaw(this, &FAnalyticsProviderTelescope::EventRequestComplete);
    HttpRequest->ProcessRequest();

}


void TelescopeEvents::Tutorials(
    const int32 &appversionid,
    const int32 &cheater,
    const FString &country,
    const int32 &deviceid,
    const FDateTime& eventtime_daily,
    const int32 &firstappversionid,
    const int32 &level,
    const FString &locale,
    const int32 &osversionid,
    const int32& paying_status,
    const int32 &paymentcount,
    const double &paymentsum,
    const int32 &sbspaymentcount,
    const double &sbspaymentsum,
    const int32 &step,
    const int32 &tester
    )
{

    FDateTime created = FDateTime::Now()

    TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
    
    JsonObject->SetStringField("entityName", "IngamePurchases");
    JsonObject->SetStringField("type", "insert");
    JsonObject->SetStringField("id", "playerIdHere");

    TSharedPtr<FJsonObject> JsonValue = MakeShareable(new FJsonObject);


    JsonValue->SetNumberField("appversionid", appversionid);
    JsonValue->SetNumberField("cheater", cheater);
    JsonValue->SetStringField("country", country);
    JsonValue->SetNumberField("deviceid", deviceid);
    JsonValue->SetNumberField("firstappversionid", firstappversionid);
    JsonValue->SetNumberField("level", level);
    JsonValue->SetStringField("locale", locale);
    JsonValue->SetNumberField("osversionid", osversionid);
    JsonValue->SetNumberField("paymentcount", paymentcount);
    JsonValue->SetNumberField("paymentsum", paymentsum);
    JsonValue->SetNumberField("sbspaymentcount", sbspaymentcount);
    JsonValue->SetNumberField("sbspaymentsum", sbspaymentsum);
    JsonValue->SetNumberField("step", step);
    JsonValue->SetNumberField("tester", tester);

    JsonObject->SetObjectField("value", JsonValue);

    FJsonSerializer::Serialize(JsonObject.ToSharedRef(), JsonWriter);
    FString JsonString;
    TSharedRef<TJsonWriter<>> JsonWriter = TJsonWriterFactory<>::Create(&JsonString);

    // HTTP Request
    const FString Apikey = GetConfigValue.Execute(TEXT("TelescopeApikey"), true);

    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest = FHttpModule::Get().CreateRequest();
    HttpRequest->SetVerb("POST");
    HttpRequest->SetHeader("Content-Type", "application/json");
    HttpRequest->SetURL(GetAPIURL() + Apikey);
    HttpRequest->SetContentAsString(JsonString);

    HttpRequest->OnProcessRequestComplete().BindRaw(this, &FAnalyticsProviderTelescope::EventRequestComplete);
    HttpRequest->ProcessRequest();

}








void TelescopeEvents::IngamePurchases(
    const int32& amount,
    const int32 &appversionid,
    const int32 &cheater,
    const FString &country,
    const FString &currency,
    const FString &item,
    const FString &itemtype,
    const int32 &deviceid,
    const int32 &firstappversionid,
    const int32 &level,
    const FString &locale,
    const int32 &osversionid,
    const int32 &p1,
    const int32 &paying_status,
    const int32 &paymentcount,
    const double &paymentsum,
    const double &price,
    const int32 &sbspaymentcount,
    const double &sbspaymentsum,
    const int32 &tester)
{

    FDateTime created = FDateTime::Now()

    TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
    
    JsonObject->SetStringField("entityName", "IngamePurchases");
    JsonObject->SetStringField("type", "insert");
    JsonObject->SetStringField("id", "playerIdHere");

    TSharedPtr<FJsonObject> JsonValue = MakeShareable(new FJsonObject);

    JsonValue->SetNumberField("amount", amount);
    JsonValue->SetNumberField("appversionid", appversionid);
    JsonValue->SetNumberField("cheater", cheater);
    JsonValue->SetStringField("country", country);
    JsonValue->SetStringField("currency", currency);
    JsonValue->SetStringField("item", item);
    JsonValue->SetStringField("itemtype", itemtype);
    JsonValue->SetNumberField("deviceid", deviceid);
    JsonValue->SetNumberField("firstappversionid", firstappversionid);
    JsonValue->SetNumberField("level", level);
    JsonValue->SetStringField("locale", locale);
    JsonValue->SetNumberField("osversionid", osversionid);
    JsonValue->SetNumberField("p1", p1);
    JsonValue->SetNumberField("paying_status", paying_status);
    JsonValue->SetNumberField("paymentcount", paymentcount);
    JsonValue->SetNumberField("paymentsum", paymentsum);
    JsonValue->SetNumberField("price", price);
    JsonValue->SetNumberField("sbspaymentcount", sbspaymentcount);
    JsonValue->SetNumberField("sbspaymentsum", sbspaymentsum);
    JsonValue->SetNumberField("tester", tester);

    JsonObject->SetObjectField("value", JsonValue);

    FJsonSerializer::Serialize(JsonObject.ToSharedRef(), JsonWriter);
    FString JsonString;
    TSharedRef<TJsonWriter<>> JsonWriter = TJsonWriterFactory<>::Create(&JsonString);

    // HTTP Request
    const FString Apikey = GetConfigValue.Execute(TEXT("TelescopeApikey"), true);

    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest = FHttpModule::Get().CreateRequest();
    HttpRequest->SetVerb("POST");
    HttpRequest->SetHeader("Content-Type", "application/json");
    HttpRequest->SetURL(GetAPIURL() + Apikey);
    HttpRequest->SetContentAsString(JsonString);

    HttpRequest->OnProcessRequestComplete().BindRaw(this, &FAnalyticsProviderTelescope::EventRequestComplete);
    HttpRequest->ProcessRequest();

}
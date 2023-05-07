// Copyright 2017 Treasure Data, Inc. All Rights Reserved.

#pragma once

#include "Interfaces/IAnalyticsProviderModule.h"
#include "Modules/ModuleManager.h"

class IAnalyticsProvider;

class FAnalyticsTelescope : public IAnalyticsProviderModule
{
	TSharedPtr<IAnalyticsProvider> Provider;

 public:
	 // Treasure Data Constants
	 static inline FAnalyticsTelescope& Get()
	 {
		 return FModuleManager::LoadModuleChecked< FAnalyticsTelescope >("Telescope");
	 }

 public:
	virtual TSharedPtr<IAnalyticsProvider> CreateAnalyticsProvider(const FAnalyticsProviderConfigurationDelegate& GetConfigValue) const override;

 private:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
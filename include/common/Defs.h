#pragma once

#include <string_view>

namespace Akr
{
  class Constants
  {
  public:
  static constexpr std::string_view kGameTitle = "Practicum Imperialis";
  static constexpr std::string_view kGameVersion = "0.1.0";

  static constexpr int kDefaultScreenWidth = 800;
  static constexpr int kDefaultScreenHeight = 600;

  static constexpr int kDefaultFps = 60;
  static constexpr int kDefaultTps = 60;

  static constexpr int kDefaultTileSize = 32;
  static constexpr int kDefaultTileMapWidth = 25;
  static constexpr int kDefaultTileMapHeight = 19;

  static constexpr int kDefaultTileMapPixelWidth = kDefaultTileSize * kDefaultTileMapWidth;

  static constexpr int kScreenWidth = 1280;
  static constexpr int kScreenHeight = 720;

  static constexpr int kTileSize = 32;
  static constexpr int kTileMapWidth = 40;
  static constexpr int kTileMapHeight = 30;

  static constexpr int kTileMapPixelWidth = kTileSize * kTileMapWidth;

  static constexpr int kMaxEntities = 1000;

  static constexpr int kMaxResources = 100;

  static constexpr int kMaxPlayers = 4;

  static constexpr int kMaxLevels = 10;

  static constexpr int kMaxScore = 100;

  static constexpr int kMaxHealth = 100;

  static constexpr int kMaxSpeed = 10;

  static constexpr int kMaxDamage = 50;

  static constexpr int kMaxRange = 100;

  static constexpr int kMaxInventorySize = 50;

  static constexpr int kMaxBuildingSize = 5;

  static constexpr int kMaxBuildingCost = 1000;

  static constexpr int kMaxBuildingHealth = 500;

  static constexpr int kMaxBuildingProduction = 10;

  static constexpr int kMaxBuildingUpgradeLevel = 3;

  static constexpr int kMaxBuildingUpgradeCost = 500;

  static constexpr int kMaxBuildingUpgradeHealth = 200;

  static constexpr int kMaxBuildingUpgradeProduction = 5;

  static constexpr int kMaxBuildingUpgradeRange = 50;

  static constexpr int kMaxBuildingUpgradeSpeed = 2;

  static constexpr int kMaxBuildingUpgradeDamage = 10;

  static constexpr int kMaxBuildingUpgradeInventorySize = 10;
  };
};
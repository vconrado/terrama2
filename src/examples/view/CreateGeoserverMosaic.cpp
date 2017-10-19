/*
  Copyright (C) 2007 National Institute For Space Research (INPE) - Brazil.

  This file is part of TerraMA2 - a free and open source computational
  platform for analysis, monitoring, and alert of geo-environmental extremes.

  TerraMA2 is free software: you can redistribute it and/or modify
  it under the terms of the GNU Lesser General Public License as published by
  the Free Software Foundation, either version 3 of the License,
  or (at your option) any later version.

  TerraMA2 is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public License
  along with TerraMA2. See LICENSE. If not, write to
  TerraMA2 Team at <terrama2-team@dpi.inpe.br>.
*/

/*!
  \file examples/view/CreateGeoServerMosaic.cpp

  \author Vinicius Campanha
 */

// TerraMA2

#include <terrama2/services/view/core/View.hpp>
#include <terrama2/services/view/core/DataManager.hpp>
#include <terrama2/services/view/core/Shared.hpp>
#include <terrama2/services/view/core/Utils.hpp>
#include <terrama2/services/view/core/Service.hpp>
#include <terrama2/services/view/mock/MockViewLogger.hpp>

#include <terrama2/core/Shared.hpp>

#include <terrama2/core/utility/Utils.hpp>
#include <terrama2/core/utility/TerraMA2Init.hpp>
#include <terrama2/core/utility/SemanticsManager.hpp>
#include <terrama2/core/utility/ServiceManager.hpp>
#include <terrama2/core/utility/TimeUtils.hpp>

#include <terrama2/core/data-model/DataManager.hpp>
#include <terrama2/core/data-model/DataSet.hpp>
#include <terrama2/core/data-model/DataSetGrid.hpp>
#include <terrama2/core/data-model/Filter.hpp>
#include <terrama2/core/data-model/DataProvider.hpp>

#include <terrama2/impl/Utils.hpp>

#include <examples/data/Geotiff.hpp>

#include <terralib/dataaccess/datasource/DataSourceFactory.h>
// Qt
#include <QCoreApplication>
#include <QUrl>
#include <QTimer>

// STL
#include <memory>

using namespace terrama2::services::view::core;
using ::testing::_;

terrama2::services::view::core::ViewPtr newView()
{
  auto view = new terrama2::services::view::core::View();
  terrama2::services::view::core::ViewPtr viewPtr(view);

  view->id = 1;
  view->active = true;
  view->projectId = 1;
  view->serviceInstanceId = 1;

  view->viewName = "MosaicExample";

  view->dataSeriesID = 9;
  view->filter = terrama2::core::Filter();

  return viewPtr;
}

int main(int argc, char** argv)
{
  try
  {

    QCoreApplication a(argc, argv);

    std::locale::global(std::locale::classic());

    terrama2::core::TerraMA2Init terramaRaii("example", 0);
    Q_UNUSED(terramaRaii);

    terrama2::core::registerFactories();

    auto& serviceManager = terrama2::core::ServiceManager::getInstance();

    auto dataManager = std::make_shared<terrama2::services::view::core::DataManager>();

    auto loggerCopy = std::make_shared<terrama2::core::MockViewLogger>();

    EXPECT_CALL(*loggerCopy, setConnectionInfo(::testing::_)).WillRepeatedly(::testing::Return());
    EXPECT_CALL(*loggerCopy, setTableName(::testing::_)).WillRepeatedly(::testing::Return());
    EXPECT_CALL(*loggerCopy, getLastProcessTimestamp(::testing::_)).WillRepeatedly(::testing::Return(nullptr));
    EXPECT_CALL(*loggerCopy, getDataLastTimestamp(::testing::_)).WillRepeatedly(::testing::Return(nullptr));
    EXPECT_CALL(*loggerCopy, done(::testing::_, ::testing::_)).WillRepeatedly(::testing::Return());
    EXPECT_CALL(*loggerCopy, start(::testing::_)).WillRepeatedly(::testing::Return(0));
    EXPECT_CALL(*loggerCopy, isValid()).WillRepeatedly(::testing::Return(true));

    te::core::URI uri("pgsql://"+TERRAMA2_DATABASE_USERNAME+ ":"+TERRAMA2_DATABASE_PASSWORD+"@"+TERRAMA2_DATABASE_HOST+":"+TERRAMA2_DATABASE_PORT+"/"+TERRAMA2_DATABASE_DBNAME);
    EXPECT_CALL(*loggerCopy, getConnectionInfo()).WillRepeatedly(::testing::Return(uri));

    EXPECT_CALL(*loggerCopy, setStartProcessingTime(::testing::_, ::testing::_)).WillRepeatedly(::testing::Return());
    EXPECT_CALL(*loggerCopy, setEndProcessingTime(::testing::_, ::testing::_)).WillRepeatedly(::testing::Return());
    EXPECT_CALL(*loggerCopy, result(::testing::_, ::testing::_, ::testing::_)).WillRepeatedly(::testing::Return());

    auto logger = std::make_shared<terrama2::core::MockViewLogger>();

    //::testing::DefaultValue<RegisterId>::Set(1);
    EXPECT_CALL(*logger, setConnectionInfo(::testing::_)).WillRepeatedly(::testing::Return());
    EXPECT_CALL(*logger, setTableName(::testing::_)).WillRepeatedly(::testing::Return());
    EXPECT_CALL(*logger, getLastProcessTimestamp(::testing::_)).WillRepeatedly(::testing::Return(nullptr));
    EXPECT_CALL(*logger, getDataLastTimestamp(::testing::_)).WillRepeatedly(::testing::Return(nullptr));
    EXPECT_CALL(*logger, done(::testing::_, ::testing::_)).WillRepeatedly(::testing::Return());
    EXPECT_CALL(*logger, start(::testing::_)).WillRepeatedly(::testing::Return(0));
    EXPECT_CALL(*logger, clone()).WillRepeatedly(::testing::Return(loggerCopy));
    EXPECT_CALL(*logger, isValid()).WillRepeatedly(::testing::Return(true));
    EXPECT_CALL(*logger, getConnectionInfo()).WillRepeatedly(::testing::Return(uri));

    EXPECT_CALL(*logger, setStartProcessingTime(::testing::_, ::testing::_)).WillRepeatedly(::testing::Return());
    EXPECT_CALL(*logger, setEndProcessingTime(::testing::_, ::testing::_)).WillRepeatedly(::testing::Return());
    EXPECT_CALL(*logger, result(::testing::_, ::testing::_, ::testing::_)).WillRepeatedly(::testing::Return());



    Service service(dataManager);
    serviceManager.setInstanceId(1);
    serviceManager.setLogger(logger);
    serviceManager.setLogConnectionInfo(te::core::URI(""));

    service.setLogger(logger);
    service.start(1);

    auto dataProvider = terrama2::geotiff::dataProviderFileGrid();
    dataManager->add(dataProvider);

    auto dataSeries = terrama2::geotiff::dataSeriesHumidity(dataProvider);
    dataManager->add(dataSeries);


    auto view = newView();
    dataManager->add(view);

    terrama2::services::view::core::View::Legend legend;

    legend.operation = terrama2::services::view::core::View::Legend::OperationType::VALUE;

    legend.metadata.emplace("creation_type", "editor");
    legend.metadata.emplace("band_number", "0");
    legend.metadata.emplace("dummy", "0");

    {
      terrama2::services::view::core::View::Legend::Rule rule;
      rule.title = "title1";
      rule.value = "0";
      rule.color = "#E18181FF";
      rule.isDefault = false;

      legend.rules.push_back(rule);
    }

    {
      terrama2::services::view::core::View::Legend::Rule rule;
      rule.title = "title2";
      rule.value = "1";
      rule.color = "#0019FFFF";
      rule.isDefault = false;

      legend.rules.push_back(rule);
    }

    QJsonObject additionalIfo;
    additionalIfo.insert("maps_server", QString("http://admin:geoserver@localhost:8080/geoserver"));

    service.updateAdditionalInfo(additionalIfo);

    service.addToQueue(view->id, terrama2::core::TimeUtils::nowUTC());

    QTimer timer;
    QObject::connect(&timer, SIGNAL(timeout()), QCoreApplication::instance(), SLOT(quit()));
    timer.start(10000);
    a.exec();

    service.stopService();

  }
  catch(...)
  {
    std::cout << "\n\nException...\n" << std::endl;
  }

  return 0;
}

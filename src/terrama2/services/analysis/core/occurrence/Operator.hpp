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
  \file terrama2/services/analysis/core/occurrence/Operator.hpp

  \brief Contains occurrence analysis operators.

  \author Paulo R. M. Oliveira
*/


#ifndef ANALYSIS_CORE_OCCURRENCE_OPERATOR_HPP
#define ANALYSIS_CORE_OCCURRENCE_OPERATOR_HPP

// TerraMA2
#include "../PythonInterpreter.hpp"
#include "../BufferMemory.hpp"
#include "../Analysis.hpp"

// STL
#include <string>


namespace terrama2
{
  namespace services
  {
    namespace analysis
    {
      namespace core
      {
        namespace occurrence
        {

          /*!
            \brief It calculates the maximum value of the attribute of occurrences in the monitored object area.

            \param statisticOperation The statistic operation called by the script.
            \param dataSeriesName DataSeries name.
            \param buffer Buffer to be used in the monitored object.
            \param dateFilter Time filter for the data.
            \param attribute Name of the attribute to be used in statistic operator.
            \param aggregationBuffer Buffer configuration to be used to aggregate occurrences in the same area.
            \param restriction SQL restriction.
            \return The result of the selected operation.
          */
          double operatorImpl(terrama2::services::analysis::core::StatisticOperation statisticOperation,
                              const std::string& dataSeriesName, terrama2::services::analysis::core::Buffer buffer,
                              const std::string& dateFilter,
                              terrama2::services::analysis::core::Buffer aggregationBuffer,
                              const std::string& attribute,
                              terrama2::services::analysis::core::StatisticOperation aggregationStatisticOperation,
                              const std::string& restriction);

          /*!
            \brief It calculates the count of occurrences in the monitored object.

            \param dataSeriesName DataSeries name.
            \param buffer Buffer to be used in the monitored object.
            \param dateFilter Time filter for the data.
            \param restriction SQL restriction.

            \return The number of occurrences in the monitored object.
          */
          int count(const std::string& dataSeriesName, terrama2::services::analysis::core::Buffer buffer,
                    const std::string& dateFilter, const std::string& restriction= "");

          /*!
            \brief It calculates the maximum value of the attribute of occurrences in the monitored object area.

            \param dataSeriesName DataSeries name.
            \param buffer Buffer to be used in the monitored object.
            \param dateFilter Time filter for the data.
            \param attribute Name of the attribute to be used in statistic operator.
            \param restriction SQL restriction.
            \return The minimum value of the attribute of occurrences in the monitored object area.
          */
          double min(const std::string& dataSeriesName, terrama2::services::analysis::core::Buffer buffer,
                     const std::string& dateFilter, const std::string& attribute, const std::string& restriction = "");

          /*!
            \brief It calculates the maximum value of the attribute of occurrences in the monitored object area.

            \param dataSeriesName DataSeries name.
            \param buffer Buffer to be used in the monitored object.
            \param dateFilter Time filter for the data.
            \param attribute Name of the attribute to be used in statistic operator.
            \param restriction SQL restriction.
            \return The maximum value of the attribute of occurrences in the monitored object area.
          */
          double max(const std::string& dataSeriesName, terrama2::services::analysis::core::Buffer buffer,
                     const std::string& dateFilter,
                     const std::string& attribute, const std::string& restriction = "");

          /*!
            \brief It calculates the mean value of the attribute of occurrences in the monitored object area.

            \param dataSeriesName DataSeries name.
            \param buffer Buffer to be used in the monitored object.
            \param dateFilter Time filter for the data.
            \param attribute Name of the attribute to be used in statistic operator.
            \param restriction SQL restriction.
            \return The mean value of the attribute of occurrences in the monitored object area.
          */
          double mean(const std::string& dataSeriesName, terrama2::services::analysis::core::Buffer buffer,
                      const std::string& dateFilter,
                      const std::string& attribute, const std::string& restriction = "");

          /*!
            \brief It calculates the median value of the attribute of occurrences in the monitored object area.

            \param dataSeriesName DataSeries name.
            \param buffer Buffer to be used in the monitored object.
            \param dateFilter Time filter for the data.
            \param attribute Name of the attribute to be used in statistic operator.
            \param restriction SQL restriction.
            \return The median value of the attribute of occurrences in the monitored object area.
          */
          double median(const std::string& dataSeriesName, terrama2::services::analysis::core::Buffer buffer,
                        const std::string& dateFilter,
                        const std::string& attribute, const std::string& restriction = "");

          /*!
            \brief It calculates the sum of values of the attribute of occurrences in the monitored object area.

            \param dataSeriesName DataSeries name.
            \param buffer Buffer to be used in the monitored object.
            \param dateFilter Time filter for the data.
            \param attribute Name of the attribute to be used in statistic operator.
            \param restriction SQL restriction.
            \return The sum of values of the attribute of occurrences in the monitored object area.
          */
          double sum(const std::string& dataSeriesName, terrama2::services::analysis::core::Buffer buffer,
                     const std::string& dateFilter,
                     const std::string& attribute, const std::string& restriction = "");

          /*!
            \brief It calculates the median value of the attribute of occurrences in the monitored object area.

            \param dataSeriesName DataSeries name.
            \param buffer Buffer to be used in the monitored object.
            \param dateFilter Time filter for the data.
            \param attribute Name of the attribute to be used in statistic operator.
            \param restriction SQL restriction.
            \return The median value of the attribute of occurrences in the monitored object area.
          */
          double standardDeviation(const std::string& dataSeriesName, terrama2::services::analysis::core::Buffer buffer,
                                   const std::string& dateFilter,
                                   const std::string& attribute, const std::string& restriction = "");


        }   // end namespace occurrence
      }     // end namespace core
    }       // end namespace analysis
  }         // end namespace services
}           // end namespace terrama2

#endif //ANALYSIS_CORE_OCCURRENCE_OPERATOR_HPP
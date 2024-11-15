#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "TrackingSourcesSingly.h"
#include "ReadData.h"
#include "LibConverterUtils.h"
#include "FilterChain.h"
#include "SourcesReader.h"

using namespace testing;

class MockTestTrackingSourceSingle : public modules::TrackingSourcesSingly
{
public:
	MockTestTrackingSourceSingle() : modules::TrackingSourcesSingly()
	{
		conf1::FhssConfigure configuration;
		
		// configuration for UKFilter
		configuration.SetDoubleProperty("UKFFilter.dt", 2.0);
		// common tracker configuiration
		configuration.SetIntegerProperty("tracker.numberSignalOfTrackSources", static_cast<long long>(100));
		// configuration for trackingTask
		configuration.SetStringProperty("trackerTask.initCoordSours", "0, 62.73117, 9.31707, 20.23022, 3347.05788");
		configuration.SetDoubleProperty("trackerTask.coordPostLatitude", 59.60438);
		configuration.SetDoubleProperty("trackerTask.coordPostLongitude", 29.27288);
		configuration.SetDoubleProperty("trackerTask.coordPostAltitude", 0.0);

		configure(configuration);
	}

	virtual ~MockTestTrackingSourceSingle()
	{
	}

	std::vector<std::pair<unsigned int, std::pair<fhss::GeographicalCoordinates, double> > > ParsingString(const std::string &propertyInit)
	{
		return modules::TrackingSourcesSingly::ParseStringInitCoord(propertyInit);
	}

	void process(common::DataType dataType, common::Any any, unsigned long long id, long long timeStampCur)
	{
		modules::TrackingSourcesSingly::handleData(dataType, any, id, timeStampCur);
	}

	double calculationHS(const fhss::LocalCoordinates &coordS)
	{
		return modules::TrackingSourcesSingly::CalculationHSources(getCoordPost(), coordS);
	}

	double calculationDist(common::SourcesTracking &sourcesTrackOUt)
	{
		return CalculationDistance(sourcesTrackOUt);
	}
};

class TestTrackingSourcesSingly : public Test
{
public:
	TestTrackingSourcesSingly()
	{}

	virtual ~TestTrackingSourcesSingly()
	{}
};

TEST_F(TestTrackingSourcesSingly, parsingString)
{
	MockTestTrackingSourceSingle testIn;
	std::string propertyInit = " 0, 60.0, 30.0, 100.0, 3500.0; 1, 60.1, 30.1, 100.0, 3600.0; 2, 61.0, 31.0, 200.0, 3500.0";
	std::vector<std::pair<unsigned int, std::pair<fhss::GeographicalCoordinates, double> > > testDataExp = testIn.ParsingString(propertyInit);
	 
	EXPECT_EQ(testDataExp.size(), 3);

	EXPECT_EQ(testDataExp[0].first, 0);
	EXPECT_NEAR(testDataExp[0].second.first.latitude, 60.0, 1e-4);
	EXPECT_NEAR(testDataExp[0].second.first.longitude, 30.0, 1e-4);
	EXPECT_NEAR(testDataExp[0].second.first.altitude, 100.0, 1e-4);
	EXPECT_NEAR(testDataExp[0].second.second, 3500.0, 1e-4);
	EXPECT_EQ(testDataExp[1].first, 1);
	EXPECT_NEAR(testDataExp[1].second.first.latitude, 60.1, 1e-4);
	EXPECT_NEAR(testDataExp[1].second.first.longitude, 30.1, 1e-4);
	EXPECT_NEAR(testDataExp[1].second.first.altitude, 100.0, 1e-4);
	EXPECT_NEAR(testDataExp[1].second.second, 3600.0, 1e-4);
	EXPECT_EQ(testDataExp[2].first, 2);
	EXPECT_NEAR(testDataExp[2].second.first.latitude, 61.0, 1e-4);
	EXPECT_NEAR(testDataExp[2].second.first.longitude, 31.0, 1e-4);
	EXPECT_NEAR(testDataExp[2].second.first.altitude, 200.0, 1e-4);
	EXPECT_NEAR(testDataExp[2].second.second, 3500.0, 1e-4);
}

TEST_F(TestTrackingSourcesSingly, calculationInformTracking)
{
	// чначало дописать функции вычисления!!!!!!!!!

}

TEST_F(TestTrackingSourcesSingly, calculationHSources)
{
	MockTestTrackingSourceSingle testIn;

	std::vector<double> xTrack = { -1142998.02767, -1349562.58030, -8331446.95088 };
	std::vector<double> yTrack = { 365385.21978, 235871.36733, 4637979.49645 };
	std::vector<double> zTrack = { -229937.90542, -220894.37190, -479954.65151 };

	std::vector<double> hExp = { -114219.47191, -70696.73179, 4827320.70327 };
	
	for (unsigned int it = 0; it < xTrack.size(); ++it)
	{
		fhss::LocalCoordinates coordS(xTrack[it], yTrack[it], zTrack[it]);
		double h = testIn.calculationHS(coordS);
		EXPECT_NEAR(h, hExp[it], 1e-3);
	}
}

TEST_F(TestTrackingSourcesSingly, calculationDistance)
{
	MockTestTrackingSourceSingle testIn;

	std::vector<double> xTrack = { -1142998.02767, -1349562.58030, -1561227.74748, -1848013.47149 };
	std::vector<double> yTrack = { 365385.21978, 235871.36733, 157115.86772, 224198.52749 };
	std::vector<double> zTrack = { -229937.90542, -220894.37190, -222352.28431, -235588.36156 };

	std::vector<double> distExp = { -1.0, 243976.51091, 225846.62323, 294824.23319 };

	common::SourcesTracking testSource;
	double dist = 0.0;
	for (unsigned int it = 0; it < xTrack.size(); ++it)
	{
		fhss::LocalCoordinates coordLocS(xTrack[it], yTrack[it], zTrack[it]);
		testSource.addCoordSourceLocal(coordLocS);
		dist = testIn.calculationDist(testSource);
		EXPECT_NEAR(dist, distExp[it], 1e-3);
	}
}

TEST_F(TestTrackingSourcesSingly, getInitCoordUKF)
{
	// чначало дописать функции вычисления!!!!!!!!!

}

TEST_F(TestTrackingSourcesSingly, getCoordPointBy)
{
	// чначало дописать функции вычисления!!!!!!!!!

}
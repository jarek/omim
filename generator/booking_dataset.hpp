#pragma once

#include "generator/osm_element.hpp"

#include "boost/geometry.hpp"
#include "boost/geometry/geometries/point.hpp"
#include "boost/geometry/geometries/box.hpp"
#include "boost/geometry/index/rtree.hpp"

#include "std/function.hpp"
#include "std/string.hpp"

class BookingDataset
{
public:
  struct BookingHotel
  {
    enum class Fields : size_t
    {
      Id = 0,
      Latitude = 1,
      Longtitude = 2,
      Name = 3,
      Address = 4,
      Stars = 5,
      PriceCategory = 6,
      RatingBooking = 7,
      RatingUsers = 8,
      DescUrl = 9,
      Type = 10,
      
      Counter
    };
    
    uint32_t id = 0;
    double lat = 0.0;
    double lon = 0.0;
    string name;
    string address;
    uint32_t stars = 0;
    uint32_t priceCategory = 0;
    double ratingBooking = 0.0;
    double ratingUser = 0.0;
    string descUrl;
    uint32_t type = 0;
    
    constexpr size_t Index(Fields field) const { return static_cast<size_t>(field); }
    constexpr size_t FieldsCount() const { return static_cast<size_t>(Fields::Counter); }
    
    BookingHotel(string const &src);
  };

  BookingDataset(string const & dataPath);
  
  bool Filter(OsmElement const & e) const;
  void BuildFeatures(function<void(OsmElement *)> const & fn) const;
  
protected:
  vector<BookingHotel> m_hotels;

  // create the rtree using default constructor
  using TPoint = boost::geometry::model::point<float, 2, boost::geometry::cs::cartesian>;
  using TBox = boost::geometry::model::box<TPoint>;
  using TValue = pair<TBox, size_t>;

  boost::geometry::index::rtree<TValue, boost::geometry::index::quadratic<16>> m_rtree;
  
  void LoadBookingHotels(string const & path);
  bool MatchWithBooking(OsmElement const & e) const;
};

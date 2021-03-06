/** level.h
*
* Copyright (c) 2019 Navigine.
*
*/

#ifndef NAVIGINE_LEVEL_H
#define NAVIGINE_LEVEL_H

#include <string>
#include <vector>
#include <map>
#include <unordered_map>

#include "boost_geometry_adaptation.h"
#include "level_geometry.h"
#include "graph.h"
#include "radiomap.h"
#include "reference_point.h"
#include "transmitter.h"
#include "navigation_input.h"

namespace navigine {
namespace navigation_core {

DECLARE_IDENTIFIER(LevelId)

class Level
{
public:
  Level(const LevelId& id, const GeoPoint& bindingPoint)
    : mId (id)
    , mBindingPoint (bindingPoint)
  {}

  void addTransmitters(const XYZTransmitters& transmitters);
  void setReferencePoints(const XYReferencePoints& referencePoints);
  void setGraph(const Graph<XYPoint>& graph);
  void setGeometry(const LevelGeometry &levelGeometry);

  const LevelId& id() const;
  const GeoPoint& bindingPoint() const;

  bool containsTransmitter(const TransmitterId& txId) const;
  const Transmitter<XYZPoint>& transmitter(const TransmitterId& txId) const;

  const Radiomap& radiomap() const;
  const Graph<XYPoint>& graph() const;
  const LevelGeometry& geometry() const;

private:
  const LevelId mId;
  const GeoPoint mBindingPoint;

  std::unordered_map<TransmitterId, Transmitter<XYZPoint>, HasherTransmitterId> mTransmitters;
  Radiomap mRadiomap;
  LevelGeometry mGeometry;
  Graph<XYPoint> mGraph;
};

typedef std::vector<std::unique_ptr<Level> >::const_iterator LevelIterator;
typedef std::vector<std::unique_ptr<Level> > Levels;

RadioMeasurementsData getLevelRadioMeasurements(
  const Level& level,
  const RadioMeasurementsData& radioMsr);

} } // namespace navigine::navigation_core

#endif // NAVIGINE_LEVEL_H

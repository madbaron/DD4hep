//==========================================================================
//  AIDA Detector description implementation 
//--------------------------------------------------------------------------
// Copyright (C) Organisation europeenne pour la Recherche nucleaire (CERN)
// All rights reserved.
//
// For the licensing terms see $DD4hepINSTALL/LICENSE.
// For the list of contributors see $DD4hepINSTALL/doc/CREDITS.
//
//  RootDictionary.h
//
//
//  M.Frank
//
//==========================================================================
#ifndef DDCORE_SRC_ROOTDICTIONARY_H
#define DDCORE_SRC_ROOTDICTIONARY_H

// Framework include files
#include "Evaluator/Evaluator.h"
#include "DD4hep/DD4hepRootPersistency.h"
#include "DD4hep/Printout.h"
#include "DD4hep/Grammar.h"
#include "DD4hep/detail/ObjectsInterna.h"
#include "DD4hep/detail/DetectorInterna.h"
#include "DD4hep/detail/ConditionsInterna.h"
#include "DD4hep/detail/AlignmentsInterna.h"
#include "DD4hep/detail/VolumeManagerInterna.h"

#include "DD4hep/World.h"
#include "DD4hep/DD4hepUI.h"
#include "DD4hep/Callback.h"
#include "DD4hep/Conditions.h"
#include "DD4hep/Alignments.h"
#include "DD4hep/FieldTypes.h"
#include "DD4hep/DetectorData.h"
#include "DD4hep/DetectorProcessor.h"
#include "DD4hep/ComponentProperties.h"
#include "DD4hep/DetectorImp.h"

// C/C++ include files
#include <vector>
#include <map>
 #include <string>

#include "TRint.h"

namespace dd4hep {
  namespace cond {}
  namespace align {}
  namespace detail {}
  void run_interpreter(const std::string& name)  {
    std::pair<int, char**> a(0,0);
    TRint app(name.c_str(), &a.first, a.second);
    app.Run();
  }

  tools::Evaluator& evaluator();
  tools::Evaluator& g4Evaluator();

  std::size_t always (const std::string& src, const std::string& msg) { return printout(ALWAYS,  src, msg); }
  std::size_t verbose(const std::string& src, const std::string& msg) { return printout(VERBOSE, src, msg); }
  std::size_t debug  (const std::string& src, const std::string& msg) { return printout(DEBUG,   src, msg); }
  std::size_t info   (const std::string& src, const std::string& msg) { return printout(INFO,    src, msg); }
  std::size_t warning(const std::string& src, const std::string& msg) { return printout(WARNING, src, msg); }
  std::size_t error  (const std::string& src, const std::string& msg) { return printout(ERROR,   src, msg); }
  std::size_t fatal  (const std::string& src, const std::string& msg) { return printout(FATAL,   src, msg); }
  void        exception(const std::string& src, const std::string& msg) { except(src, "%s", msg.c_str()); }

  namespace detail {
    /// Helper to invoke the ROOT interpreter
    struct interp  {
    public:
      interp() = default;
      virtual ~interp() = default;
      static void run(const std::string& name)  {
	std::pair<int, char**> a(0,0);
	TRint app(name.c_str(), &a.first, a.second);
	app.Run();
      }
    };
    //// Helper to access the evaluator instances
    struct eval  {
    public:
      eval() = default;
      virtual ~eval() = default;
      static dd4hep::tools::Evaluator& instance()     {
	return dd4hep::evaluator();
      }
      static dd4hep::tools::Evaluator& g4instance()   {
	return dd4hep::g4Evaluator();
      }
    };
  }
}

namespace dd4hep   {   namespace Parsers   {
    int parse(dd4hep::AlignmentData&, const std::string&);
    int parse(dd4hep::detail::AlignmentObject&, const std::string&);
  }}

// -------------------------------------------------------------------------
// Regular dd4hep dictionaries
// -------------------------------------------------------------------------
#ifdef DD4HEP_DICTIONARY_MODE
#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;

#pragma link C++ namespace dd4hep;

#pragma link C++ namespace dd4hep::tools;
#pragma link C++ class dd4hep::tools::Evaluator;
#pragma link C++ function dd4hep::evaluator;
#pragma link C++ function dd4hep::g4Evaluator;

#pragma link C++ namespace dd4hep::detail;
#pragma link C++ namespace dd4hep::cond;
#pragma link C++ namespace dd4hep::align;
#pragma link C++ namespace dd4hep::DDSegmentation;

#pragma link C++ enum dd4hep::PrintLevel;
#pragma link C++ function dd4hep::always;
#pragma link C++ function dd4hep::verbose;
#pragma link C++ function dd4hep::debug;
#pragma link C++ function dd4hep::info;
#pragma link C++ function dd4hep::warning;
#pragma link C++ function dd4hep::error;
#pragma link C++ function dd4hep::fatal;
#pragma link C++ function dd4hep::except;
#pragma link C++ function dd4hep::printout;
#pragma link C++ function dd4hep::exception;

#ifndef __ROOTCLING__
template std::pair<unsigned int, std::string>;
template class dd4hep::Handle<dd4hep::NamedObject>;
template class std::pair< string, dd4hep::Handle<dd4hep::NamedObject> >;
template class std::map< string, dd4hep::Handle<dd4hep::NamedObject> >;
template class std::pair<dd4hep::Callback,unsigned long>;
#endif

#pragma link C++ class DD4hepRootPersistency+;
#pragma link C++ class DD4hepRootCheck+;

#pragma link C++ class std::pair<unsigned int,std::string>+;
//#pragma link C++ class dd4hep::Callback+;
#pragma link C++ class std::pair<dd4hep::Callback,unsigned long>+;
#pragma link C++ class dd4hep::NamedObject+;
#pragma link C++ class dd4hep::Ref_t+;
#pragma link C++ class dd4hep::Handle<dd4hep::NamedObject>+;
#pragma link C++ class std::pair<std::string, dd4hep::Handle<dd4hep::NamedObject> >+;
#pragma link C++ class std::map<std::string, dd4hep::Handle<dd4hep::NamedObject> >+;
#pragma link C++ class std::map<std::string, dd4hep::Handle<dd4hep::NamedObject> >::iterator;
#pragma link C++ class std::map<std::string, dd4hep::Handle<dd4hep::NamedObject> >::const_iterator;
#pragma link C++ class dd4hep::detail::DD4hepUI;

#ifdef R__MACOSX
// We only need these declarations for the clang compiler
#pragma link C++ function operator==( const std::map<std::string, dd4hep::Handle<dd4hep::NamedObject> >::iterator&,const std::map<std::string, dd4hep::Handle<dd4hep::NamedObject> >::iterator& );
#pragma link C++ function operator!=( const std::map<std::string, dd4hep::Handle<dd4hep::NamedObject> >::iterator&,const std::map<std::string, dd4hep::Handle<dd4hep::NamedObject> >::iterator& );
#endif

#pragma link C++ class dd4hep::BasicGrammar+;
#pragma link C++ class dd4hep::ObjectExtensions+;
template class dd4hep::Handle<TNamed>;
#pragma link C++ class dd4hep::Handle<TNamed>+;

#pragma link C++ class dd4hep::IOV+;
#pragma link C++ class dd4hep::IOVType+;
#pragma link C++ class dd4hep::OpaqueData+;
#pragma link C++ class dd4hep::OpaqueDataBlock+;

#pragma link C++ class dd4hep::Detector+;
#pragma link C++ class dd4hep::DetectorImp+;
#pragma link C++ class dd4hep::DetectorLoad+;
#pragma link C++ class dd4hep::DetectorData+;
#pragma link C++ class dd4hep::DetectorData::ObjectHandleMap+;
#pragma link C++ class dd4hep::Detector::PropertyValues+;
#pragma link C++ class dd4hep::Detector::Properties+;
#pragma link C++ class std::pair<dd4hep::IDDescriptor,dd4hep::DDSegmentation::Segmentation*>+;
#pragma link C++ class std::map<dd4hep::Readout,pair<dd4hep::IDDescriptor,dd4hep::DDSegmentation::Segmentation*> >+;

// These below are the Namedobject instances to be generated ....
//#pragma link C++ class dd4hep::Detector::HandleMap+;
//#pragma link C++ class dd4hep::Detector::HandleMap::iterator;
//#pragma link C++ class dd4hep::Detector::HandleMap::const_iterator;
//#pragma link C++ class dd4hep::Detector::HandleMap::key_type; // == string
//#pragma link C++ class dd4hep::Detector::HandleMap::value_type+;

#pragma link C++ class dd4hep::VolumeManager+;
#pragma link C++ class dd4hep::detail::VolumeManagerObject+;
#pragma link C++ class dd4hep::VolumeManagerContext+;
#pragma link C++ class dd4hep::detail::VolumeManagerContextExtension+;
#pragma link C++ class dd4hep::Handle<dd4hep::detail::VolumeManagerObject>+;
#pragma link C++ class std::pair<Long64_t,dd4hep::VolumeManager>+;
#pragma link C++ class std::map<dd4hep::DetElement,dd4hep::VolumeManager>+;
#pragma link C++ class std::map<dd4hep::VolumeID,dd4hep::VolumeManager>+;
#pragma link C++ class std::map<dd4hep::VolumeID,dd4hep::VolumeManagerContext*>+;

#pragma link C++ class dd4hep::CartesianField+;
#pragma link C++ class dd4hep::CartesianField::Object+;
#pragma link C++ class dd4hep::Handle<dd4hep::CartesianField::Object>+;
#pragma link C++ class dd4hep::OverlayedField+;
#pragma link C++ class dd4hep::OverlayedField::Object+;
#pragma link C++ class dd4hep::Handle<dd4hep::OverlayedField::Object>+;

// FieldTypes.h
#pragma link C++ class dd4hep::ConstantField+;
#pragma link C++ class dd4hep::Handle<dd4hep::ConstantField>+;
#pragma link C++ class dd4hep::SolenoidField+;
#pragma link C++ class dd4hep::Handle<dd4hep::SolenoidField>+;
#pragma link C++ class dd4hep::DipoleField+;
#pragma link C++ class dd4hep::Handle<dd4hep::DipoleField>+;

#pragma link C++ class dd4hep::IDDescriptor+;
#pragma link C++ class dd4hep::IDDescriptorObject+;
#pragma link C++ class dd4hep::Handle<dd4hep::IDDescriptorObject>+;

// Objects.h
#pragma link C++ class dd4hep::Author+;
#pragma link C++ class std::vector<dd4hep::Author>+;

#pragma link C++ class dd4hep::Header+;
#pragma link C++ class dd4hep::HeaderObject+;
#pragma link C++ class dd4hep::Handle<dd4hep::HeaderObject>+;

#pragma link C++ class dd4hep::Constant+;
#pragma link C++ class dd4hep::ConstantObject+;
#pragma link C++ class dd4hep::Handle<dd4hep::ConstantObject>+;
#pragma link C++ class std::vector<dd4hep::Constant>+;

#pragma link C++ class dd4hep::Atom+;
#pragma link C++ class std::vector<dd4hep::Atom>+;
#pragma link C++ class dd4hep::Handle<TGeoElement>+;

#pragma link C++ class dd4hep::Material+;
#pragma link C++ class std::vector<dd4hep::Material>+;
#pragma link C++ class dd4hep::Handle<TGeoMedium>+;

#pragma link C++ class dd4hep::VisAttr+;
#pragma link C++ class std::vector<dd4hep::VisAttr>+;
#pragma link C++ class dd4hep::VisAttrObject+;
#pragma link C++ class dd4hep::Handle<dd4hep::VisAttrObject>+;

#pragma link C++ class dd4hep::Limit+;
#pragma link C++ class std::set<dd4hep::Limit>+;
#pragma link C++ class std::vector<dd4hep::Limit>+;
#pragma link C++ class dd4hep::LimitSet+;
#pragma link C++ class std::vector<dd4hep::LimitSet>+;
#pragma link C++ class dd4hep::LimitSetObject+;
#pragma link C++ class dd4hep::Handle<dd4hep::LimitSetObject>+;
#pragma link C++ class dd4hep::Region+;
#pragma link C++ class dd4hep::RegionObject+;
#pragma link C++ class dd4hep::Handle<dd4hep::RegionObject>+;
#pragma link C++ class std::vector<dd4hep::Region>+;

// Readout.h
#pragma link C++ class std::vector<pair<size_t,string> >+;
#pragma link C++ class dd4hep::Segmentation+;
#pragma link C++ class dd4hep::SegmentationObject+;
#pragma link C++ class dd4hep::Handle<dd4hep::SegmentationObject>+;
#pragma link C++ class dd4hep::HitCollection+;
#pragma link C++ class dd4hep::Readout+;
#pragma link C++ class dd4hep::HitCollection+;
#pragma link C++ class dd4hep::ReadoutObject+;
#pragma link C++ class dd4hep::Handle<dd4hep::ReadoutObject>+;
#pragma link C++ class std::vector<dd4hep::HitCollection>+;
#pragma link C++ class std::vector<dd4hep::Readout>+;
#pragma link C++ class std::vector<dd4hep::HitCollection*>+;
#pragma link C++ class std::vector<const dd4hep::HitCollection*>+;
#pragma link C++ class std::vector<dd4hep::IDDescriptor>+;

// Alignment stuff
#pragma link C++ class dd4hep::Delta+;
#pragma link C++ class dd4hep::Alignment+;
#pragma link C++ class dd4hep::AlignmentData+;
#pragma link C++ class dd4hep::Handle<dd4hep::AlignmentData>+;
//#pragma link C++ class dd4hep::Grammar<dd4hep::AlignmentData>+;

#pragma link C++ class dd4hep::AlignmentCondition+;
#pragma link C++ class dd4hep::detail::AlignmentObject+;
#pragma link C++ class dd4hep::Handle<dd4hep::detail::AlignmentObject>+;
#pragma link C++ class std::pair<dd4hep::DetElement,dd4hep::AlignmentCondition>+;
//#pragma link C++ class dd4hep::Grammar<dd4hep::detail::AlignmentObject>+;

#pragma link C++ class dd4hep::align::GlobalAlignment+;
#pragma link C++ class dd4hep::Handle<TGeoPhysicalNode>+;

// Conditions stuff
#pragma link C++ class dd4hep::Condition+;
#pragma link C++ class std::vector<dd4hep::Condition>+;
#pragma link C++ class dd4hep::ConditionKey+;
#pragma link C++ class std::vector<dd4hep::ConditionKey>+;
#pragma link C++ class dd4hep::detail::ConditionObject+;
#pragma link C++ class dd4hep::Handle<dd4hep::detail::ConditionObject>+;
#pragma link C++ class dd4hep::OpaqueData+;
#pragma link C++ class dd4hep::OpaqueDataBlock+;

// DetElement.h
#pragma link C++ class dd4hep::World+;
#pragma link C++ class dd4hep::WorldObject+;
#pragma link C++ class dd4hep::Handle<dd4hep::WorldObject>+;
#pragma link C++ class dd4hep::DetElement+;
#pragma link C++ class dd4hep::DetElement::Processor+;
#pragma link C++ class dd4hep::DetElementObject+;
#pragma link C++ class dd4hep::Handle<dd4hep::DetElementObject>+;
#pragma link C++ class std::vector<dd4hep::DetElement>+;
#pragma link C++ class std::pair<std::string,dd4hep::DetElement>+;
#pragma link C++ class std::map<std::string,dd4hep::DetElement>+;
#pragma link C++ class std::map<std::string,dd4hep::DetElement>::iterator;
#pragma link C++ class std::map<std::string,dd4hep::DetElement>::const_iterator;

#pragma link C++ class dd4hep::DetectorProcessor+;
#pragma link C++ class dd4hep::DetectorScanner+;

#pragma link C++ class std::pair<dd4hep::DetElement,dd4hep::VolumeManager>+;

#ifdef R__MACOSX
// We only need these declarations for the clang compiler
#pragma link C++ function operator==( const std::map<std::string, dd4hep::DetElement >::iterator&,const std::map<std::string, dd4hep::DetElement >::iterator& );
#pragma link C++ function operator!=( const std::map<std::string, dd4hep::DetElement >::iterator&,const std::map<std::string, dd4hep::DetElement >::iterator& );
#endif

#pragma link C++ class dd4hep::SensitiveDetector+;
#pragma link C++ class dd4hep::SensitiveDetectorObject+;
#pragma link C++ class dd4hep::Handle<dd4hep::SensitiveDetectorObject>+;
#pragma link C++ class vector<dd4hep::SensitiveDetector>+;

#pragma link C++ class std::pair<std::string, std::string>+;
#pragma link C++ class std::map<std::string, std::string>+;
#pragma link C++ class std::map<std::string, std::string>::iterator;
#pragma link C++ class std::map<std::string, std::string>::const_iterator;

#ifdef R__MACOSX
// We only need these declarations for the clang compiler
#pragma link C++ function operator==( const std::map<std::string, std::string>::iterator&, const std::map<std::string, std::string>::iterator& );
#pragma link C++ function operator!=( const std::map<std::string, std::string>::iterator&, const std::map<std::string, std::string>::iterator& );
#endif

#pragma link C++ class std::pair<std::string, std::map<std::string, std::string> >+;
#pragma link C++ class std::map<std::string, std::map<std::string, std::string> >+;
#pragma link C++ class std::map<std::string, std::map<std::string,std::string>>::iterator;
#pragma link C++ class std::map<std::string, std::map<std::string,std::string>>::const_iterator;

#ifdef R__MACOSX
// We only need these declarations for the clang compiler
#pragma link C++ function operator==( const std::map<std::string, std::map<std::string,std::string>>::iterator&, const std::map<std::string, std::map<std::string,std::string>>::iterator& );
#pragma link C++ function operator!=( const std::map<std::string, std::map<std::string,std::string>>::iterator&, const std::map<std::string, std::map<std::string,std::string>>::iterator& );
#endif

#pragma link C++ class dd4hep::Detector+;

#pragma link C++ class dd4hep::detail::interp;
#pragma link C++ class dd4hep::detail::eval;

#pragma link C++ function dd4hep::run_interpreter(const std::string& name);
#pragma link C++ function dd4hep::_toDictionary(const std::string&, const std::string&);
#pragma link C++ function dd4hep::toStringSolid(const TGeoShape*, int);
#pragma link C++ function dd4hep::toStringMesh(const TGeoShape*, int);
#pragma link C++ function dd4hep::toStringMesh(dd4hep::PlacedVolume, int);

#include "DD4hep/ConditionsData.h"
#pragma link C++ class dd4hep::cond::ClientData+;
#pragma link C++ class dd4hep::cond::AbstractMap+;
#pragma link C++ class dd4hep::cond::AbstractMap::Params+;

#endif  // __CINT__
#endif // DDCORE_SRC_ROOTDICTIONARY_H

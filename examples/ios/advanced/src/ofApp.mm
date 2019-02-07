//
// Copyright (c) 2019 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#include "ofApp.h"


void ofApp::setup()
{
    ofSetLogLevel(OF_LOG_VERBOSE);

    // The simplest way to get all advanced PointerEvents. This method will
    // create a subview window that will captures all touch events before they
    // are passed to the standard ofxiOSApp window.
    //
    // When calling ofx::RegisterAdvancedPointerEventsiOS(this), it is expected
    // that the following standard ofxPointer event methods are present in the
    // listener class:
    //
    //  void onPointerUp(ofx::PointerEventArgs& evt);
    //  void onPointerDown(ofx::PointerEventArgs& evt);
    //  void onPointerMove(ofx::PointerEventArgs& evt);
    //  void onPointerCancel(ofx::PointerEventArgs& evt);
    //
    // Additionally the following method must also be included:
    //
    //  void onPointerUpdate(ofx::PointerEventArgs& evt);
    //
    // The onPointerUpdate is called when iOS updates previously estimated
    // point data. If the previous points are not preserved, then these events
    // should be ignored. Otherwise, they can be matched with previous events
    // by examining the sequenceIndex() of the stored and updated events.

    ofx::RegisterAdvancedPointerEventsiOS(this);

}


void ofApp::update()
{
}


void ofApp::draw()
{
}


void ofApp::onPointerUp(ofx::PointerEventArgs& evt)
{
    addEvent(evt);
}


void ofApp::onPointerDown(ofx::PointerEventArgs& evt)
{
    addEvent(evt);
}


void ofApp::onPointerMove(ofx::PointerEventArgs& evt)
{
    addEvent(evt);
}


void ofApp::onPointerCancel(ofx::PointerEventArgs& evt)
{
    addEvent(evt);
}

void ofApp::onPointerUpdate(ofx::PointerEventArgs& evt)
{
    std::cout << "update: " << evt.sequenceIndex() << ": " << evt.eventType() << std::endl;

    auto iter = t.find(evt.sequenceIndex());
    
    if (iter != t.end())
    {
        if (!iter->second.updateEstimatedPropertiesWithEvent(evt))
        {
            std::cout << "update failed." << std::endl;
        }
    }
    else
    {
        std::cout << "-- Did not find event to update." << std::endl;
    }
}

void ofApp::addEvent(ofx::PointerEventArgs& evt)
{
//    std::cout << "add: " << evt.sequenceIndex() << ": " << std::this_thread::get_id() << " ... events.size(): " << t.size();
    // t[evt.sequenceIndex()] = evt;
    
    for (auto& e: evt.coalescedPointerEvents())
    {
        // If we want to listen to the event we need to carefully do it.
        auto i = t.insert(std::make_pair(e.sequenceIndex(), e));
        ofAddListener(i.first->second.pointerPropertyUpdate,
                      this,
                      &ofApp::pointerPropertyUpdate);
    }
    
    if (t.find(evt.sequenceIndex()) == t.end())
    {
        std::cout << "Found one that wasn't added: " << evt.eventType() << std::endl;
    }
    
    
//    evt.coalescedPointerEvents()
    
    
//    std::cout << " complete." << std::endl;
}

void ofApp::pointerPropertyUpdate(const void* source, std::string& evt)
{
    const ofx::PointerEventArgs* s = reinterpret_cast<const ofx::PointerEventArgs*>(source);
    
    std::uint64_t i = 0;
    if (s)
        i = s->sequenceIndex();
    
    std::cout << "updated: " << evt << " for seq: " << i << std::endl;
}



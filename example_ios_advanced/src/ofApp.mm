#include "ofApp.h"


void ofApp::setup()
{
    ofSetLogLevel(OF_LOG_VERBOSE);
    
    // The simplest way to get basic PointerEvents. This method will capture
    // the default touch events and convert them into pointer events.
    //
    // Due to a limitation in openFrameworks, these pointer events will not
    // have a high temporal resolution or other useful touch data available
    // on iOS. To receive advanced touch data in the pointer events, see the
    // `example_ios_advanced` example.
    //
    // If the pointer events are consumed, then the the normal touch events
    // will not be called, otherwise, they will continued to be received via:
    //
    //  void touchDown(ofTouchEventArgs& touch) override;
    //  void touchMoved(ofTouchEventArgs& touch) override;
    //  void touchUp(ofTouchEventArgs& touch) override;
    //  void touchDoubleTap(ofTouchEventArgs& touch) override;
    //  void touchCancelled(ofTouchEventArgs& touch) override;
    //
    // These standard callbacks are not included in this example for simplicity.
    //
    // When calling ofx::RegisterPointerEvents(this), it is expected that the
    // following methods are present in the listener class.
    //
    //  void onPointerUp(ofx::PointerEventArgs& evt);
    //  void onPointerDown(ofx::PointerEventArgs& evt);
    //  void onPointerMove(ofx::PointerEventArgs& evt);
    //  void onPointerCancel(ofx::PointerEventArgs& evt);
    //
    // or if pointer events can be consumed:
    //
    //  bool onPointerUp(ofx::PointerEventArgs& evt);
    //  bool onPointerDown(ofx::PointerEventArgs& evt);
    //  bool onPointerMove(ofx::PointerEventArgs& evt);
    //  bool onPointerCancel(ofx::PointerEventArgs& evt);

    ofx::RegisterPointerEventsiOS(this);
    
    ofAddListener(ofx::PointerEventsManager::instance().eventsForWindow(nullptr)->pointerUpdate, this, &ofApp::onPointerUpdate);
    
    std::cout << t.size() << std::endl;
    
    auto iter = t.find(0);
    

}


void ofApp::update()
{
}


void ofApp::draw()
{
}

void ofApp::touchDown(ofTouchEventArgs & touch)
{
    std::cout << "down: " << touch.id << std::endl;
}


void ofApp::touchMoved(ofTouchEventArgs & touch)
{
    std::cout << "move: " << touch.id << std::endl;
}


void ofApp::touchUp(ofTouchEventArgs & touch)
{
    std::cout << "  up: " << touch.id << std::endl;
}


void ofApp::touchDoubleTap(ofTouchEventArgs & touch)
{
    std::cout << "  dt: " << touch.id << std::endl;
}


void ofApp::touchCancelled(ofTouchEventArgs & touch)
{
    std::cout << " can: " << touch.id << std::endl;
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
    std::cout << "update: " << evt.sequenceIndex() << ": " << std::this_thread::get_id() << std::endl;

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
        ofAddListener(i.first->second.pointerPropertyUpdate, this, &ofApp::pointerPropertyUpdate);
    }
    
    if (t.find(evt.sequenceIndex()) == t.end())
    {
        std::cout << "Found one that wasn't added: " << evt.eventType() << std::endl;
    }
    
    
//    evt.coalescedPointerEvents()
    
    
//    std::cout << " complete." << std::endl;
}

void ofApp::pointerPropertyUpdate(std::string& evt)
{
    std::cout << "updated: " << evt << std::endl;
}



#pragma once
#ifndef mcafee_APP_APP_H
#define mcafee_APP_APP_H

#include <ds/app/app.h>
#include <ds/debug/debug_defines.h>
#include "globals.h"
#include "model/movie_model.h"
#include "model/latest_threat_model.h"
#include "query/query_handler.h"

namespace mcafee {

class ThreatApp : public ds::App {
public:
	ThreatApp();

	void                setupServer();
	void                update();
	void                keyDown(KeyEvent);
	virtual void		keyUp(KeyEvent);
	virtual void		touchesBegan(TouchEvent& te);

	virtual void		mouseDown(MouseEvent);	
	virtual void		mouseDrag(MouseEvent);
	virtual void		mouseUp(MouseEvent);	

private:
	void				transparentScreenshot();

	typedef ds::App     inherited;
	friend class AppState;

	std::vector<MovieModel>			mMediaList;
	std::vector<TickerModel>		mNewsList;
	std::vector<LatestThreatModel>	mLatestThreats;

	// Data acquisition
	QueryHandler		mQueryEventHandler;

	Globals             mGlobals;

};

} // namespace mcafee

#endif // mcafee_APP_APP_H
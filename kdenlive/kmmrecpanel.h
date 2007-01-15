/***************************************************************************
                          KMMRecPanelimplementation.h  -  description
                             -------------------
    begin                : Mon Apr 8 2002
    copyright            : (C) 2006 by Jean-Baptiste Mardelle
    email                : jbm@ader.ch
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef KMMRECPANELIMPLEMENTATION_H
#define KMMRECPANELIMPLEMENTATION_H

#include "kmmrecpanel_ui.h"

#include "timecode.h"
#include "gentime.h"

class KdenliveDoc;

namespace Gui {

/**Implementation for the capture panel
  *@author Jean-Baptiste Mardelle
  */

    class KMMRecPanel:public KMMRecPanel_UI {
      Q_OBJECT public:
	KMMRecPanel(KdenliveDoc * document, QWidget * parent =
	    0, const char *name = 0, WFlags fl = 0);
	~KMMRecPanel();
	/** Returns the point time of the current clip. */
	GenTime point() const;
	/** Returns the inpoint time for the current clip. */
	GenTime inpoint() const;
	/** Returns the outpoint time for the current clip. */
	GenTime outpoint() const;

	private slots:		// Private slots
  /** A slider on the ruler has changed value */
	void rulerValueChanged(int ID, int value);
  /** Make sure that the edit buttons are in the correct state;have the correct image displayed */
	void updateButtons();
	 signals:		// Signals

	void playDevice();
	void pauseDevice();
	void stopDevice();
	void stepRewindDevice();
	void rewindDevice();
	void stepForwardDevice();
	void forwardDevice();
	void recDevice();


  /** Emitted when stop button pressed */
	void playStopped(const GenTime & startTime);
  /** Emitted when the seek position has changed */
	void seekPositionChanged(const GenTime &);
  /** Emitted when the outpoint position has changed */
	void outpointPositionChanged(const GenTime &);
  /** Emitted when the inpoint position has changed */
	void inpointPositionChanged(const GenTime &);
  /** Emitted by the EditPanel when the playSpeed should change. */
	void playSpeedChanged(double, const GenTime &);
  /** Emitted by the EditPanel when the playSpeed should change. */
	void playSpeedChanged(double);
  /** Emitted by the EditPanel when the playSpeed should change. */
	void playSpeedChanged(double, const GenTime &, const GenTime &);

  /** Emitted when the nextSnapMarker button has been clicked */
	void nextSnapMarkerClicked();

  /** Emitted when the previousSnapMarker button has been clicked */
	void previousSnapMarkerClicked();

/** Creates or destroys a snap marker at the current time. */
	void toggleSnapMarker();

	void activateMonitor();

      private:			// Private attributes
  /** The document associated with this edit panel */
	 KdenliveDoc * m_document;
  double m_playSpeed;
  
 // Set or stop playback.
  void setPlaying(bool play);
  Timecode tcode;
  int buttonSize;
  bool m_playSelected;
  bool m_loop;
  GenTime m_startPlayPosition;

   // True if we are playing, false otherwise.
	bool isPlaying() const {
	    if (m_pauseMode) return false;
	    return m_playSpeed != 0.0;
	};
	bool isForwarding() const {
	    return m_playSpeed > 1.0;
	};
	bool isRewinding() const {
	    return m_playSpeed < -1.0;
	};

	// True if we are only playing the section of the file between inpoint and outpoint.


	bool m_pauseMode;
    public slots:		// Public slots
  /** Seeks to the end of the ruler */
	void seekEnd();
  /** Seeks to the beginning of the ruler. */
	void seekBeginning();
  /** Steps slider value forwards one frame. */
	void stepForwards();
  /** Steps slider value one step backwards. */
	void stepBack();
  /** Called when the "stop" button has been pressed. */
	void stop();
  /** Called when the "play" button is pressed */
	void play();
  /** Called when the "play selected" button is pressed */
	void loopSelected();
  /** Sets the current seek position to the one specified */
	void seek(const GenTime & time);
  /** Alerts the edit panel that the renderer has disconnected. */
	void rendererConnected();
  /** Alerts the edit panel that the renderer has disconnected. */
	void rendererDisconnected();
  /** Sets the outpoint position to the current seek position */
	void setOutpoint();
  /** Sets the inpoint position to the current seek position */
	void setInpoint();
  /** Sets the outpoint position to the current seek position */
	void setOutpoint(const GenTime & outpoint);
  /** Sets the inpoint position to the current seek position */
	void setInpoint(const GenTime & inpoint);
  /** Toggles whether or not we are currently "playing" the inpoint/outpoint selection*/
	void togglePlaySelected();
	void toggleForward();
	void toggleRewind();
  /** called when the screen has changed it's play speed - e.g., the renderer has
  reached the end of the file. */
	void screenPlaySpeedChanged(double speed);
        /** called when the renderer stopped. */
        void screenPlayStopped();
  /**  set whether the edit panel displays that there is a snap marker at the current seek time or not */
	void setSnapMarker(bool markerHere);
	void setRecording();
	void unsetRecording();
    };

}				// namespace Gui
#endif

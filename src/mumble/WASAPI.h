// Copyright 2005-2016 The Mumble Developers. All rights reserved.
// Use of this source code is governed by a BSD-style license
// that can be found in the LICENSE file at the root of the
// Mumble source tree or at <https://www.mumble.info/LICENSE>.

#ifndef MUMBLE_MUMBLE_WASAPI_H_
#define MUMBLE_MUMBLE_WASAPI_H_

#include <QtCore/QObject>
#include <QtCore/QUuid>

#include <windows.h>
#include <mmreg.h>
#include <strsafe.h>
#include <mmdeviceapi.h>
#include <avrt.h>
#include <audioclient.h>
#include <ksmedia.h>
#include <functiondiscoverykeys.h>
#include <propidl.h>
#include <initguid.h>
#include <Audiopolicy.h>

#include "AudioInput.h"
#include "AudioOutput.h"

class WASAPISystem : public QObject {
	private:
		Q_OBJECT
		Q_DISABLE_COPY(WASAPISystem)
	public:
		static const QHash<QString, QString> getDevices(EDataFlow dataflow);
		static const QHash<QString, QString> getInputDevices();
		static const QHash<QString, QString> getOutputDevices();
		static const QList<audioDevice> mapToDevice(const QHash<QString, QString>&, const QString&);
};

class WASAPIInput : public AudioInput {
	private:
		Q_OBJECT
		Q_DISABLE_COPY(WASAPIInput)
	public:
		WASAPIInput();
		~WASAPIInput() Q_DECL_OVERRIDE;
		void run() Q_DECL_OVERRIDE;
};

class WASAPIOutput : public AudioOutput {
	private:
		Q_OBJECT
		Q_DISABLE_COPY(WASAPIOutput)
		
		bool setVolumeForSessionControl(IAudioSessionControl *control, const DWORD mumblePID, QSet<QUuid> &seen);
		bool setVolumeForSessionControl2(IAudioSessionControl2 *control2, const DWORD mumblePID, QSet<QUuid> &seen);
	protected:
		typedef QPair<float, float> VolumePair;
		QMap<ISimpleAudioVolume *, VolumePair> qmVolumes;
		void setVolumes(IMMDevice *, bool talking);
	public:
		WASAPIOutput();
		~WASAPIOutput() Q_DECL_OVERRIDE;
		void run() Q_DECL_OVERRIDE;
};

#endif


/*!
 * \file	Log.cpp
 * \brief	Logging functions for ${project}.
 */

#include "Log.h"

void LogError (const char *pBuffer)
{
	Project::Log::Error (pBuffer);
}

void LogDebug (const char *pBuffer)
{
	Project::Log::Debug (pBuffer);
}

void Project::Log::Initialize (EventHandler* pHandler)
{
	// Initialize logging handles in the VPE
	ErrorLogRemoteLoggingSet (reinterpret_cast<size_t *> (pHandler), Error);
	AssertRemoteLoggingSet (reinterpret_cast<size_t *> (pHandler), Error);
	RemoteLogEventRemoteLoggingSet (reinterpret_cast<size_t *> (pHandler), Trace);
	TraceRemoteLoggingSet (reinterpret_cast<size_t *> (pHandler), Debug);

	// Globalize the handler of this initializer
	pStaticHandler = pHandler;
}

Result Project::Log::Log (size_t *pContext, Project::Common::ServerEvent eventType, const char *pBuffer)
{
	Result hResult = Result::Error;
	PstiServerEventHandler pHandler = reinterpret_cast<PstiServerEventHandler> (pContext);

	if (nullptr != pHandler &&
		IsLogEvent (eventType))
	{
		Log (pHandler, eventType, pBuffer);
		hResult = Result::Success;
	}

	return hResult;
}

void Project::Log::Error (size_t *pContext, const char *pBuffer)
{
	Log (pContext, Common::ServerEvent::Error, pBuffer);
}

Result Project::Log::Trace (size_t *pContext, const char *pBuffer)
{
	return Log (pContext, Common::ServerEvent::Trace, pBuffer);
}

void Project::Log::Debug (size_t *pContext, const char *pBuffer)
{
	Log (pContext, Common::ServerEvent::TraceDebug, pBuffer);
}

void Project::Log::Error (const char *pBuffer)
{
	Log (pStaticHandler, Common::ServerEvent::Error, pBuffer);
}

void Project::Log::Trace (const char *pBuffer)
{
	Log (pStaticHandler, Common::ServerEvent::Trace, pBuffer);
}

void Project::Log::Debug (const char *pBuffer)
{
	Log (pStaticHandler, Common::ServerEvent::TraceDebug, pBuffer);
}

void Project::Log::Log (PstiServerEventHandler pHandler, Common::ServerEvent eventType)
{
	// Base case -- there are no more arguments to print
}

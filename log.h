
/*!
 * \file	Log.h
 * \brief	Log functions for ${project}.
 */

#pragma once

#include "Common.h"
#include "Error.h"
#include "IHoldServer.h"
#include "LoggingHooks.h"

#include <iostream>

extern void LogError (const char *pBuffer);
extern void LogDebug (const char *pBuffer);

namespace Project
{
namespace Log
{
typedef int *EventHandler;
static EventHandler pStaticHandler = nullptr;

static void Initialize (EventHandler pHandler);

static Result Log (size_t *pContext, Common::ServerEvent eventType, const char *pBuffer);

static void Error (size_t *pContext, const char *pBuffer);
static Result Trace (size_t *pContext, const char *pBuffer);
static void Debug (size_t *pContext, const char *pBuffer);

static void Error (const char *pBuffer);
static void Trace (const char *pBuffer);
static void Debug (const char *pBuffer);

static constexpr bool IsLogEvent (Common::ServerEvent eventType)
{
	bool isLogEvent = false;

	switch (eventType)
	{
		case Common::ServerEvent::Error:
		case Common::ServerEvent::Trace:
		case Common::ServerEvent::TraceDebug:
			isLogEvent = true;
			break;
		default:
			break;
	}

	return isLogEvent;
}

void Log (EventHandler pHandler, Common::ServerEvent eventType);

template <class Arg, class... Args>
void Log (EventHandler pHandler, Common::ServerEvent eventType, const Arg &arg, const Args &... args)
{
	if (nullptr != pHandler &&
		IsLogEvent (eventType))
	{
		// Print argument
		pHandler (eventType, nullptr, (void *)(arg)); // Be a void pointer and like it

		// Print other arguments
		Log (pHandler, eventType, args...);
	}
}

template <class... Args>
void Error (EventHandler pHandler, const Args &... args)
{
	Log (pHandler, Common::ServerEvent::Error, args...);
}

template <class... Args>
void Trace (EventHandler pHandler, const Args &... args)
{
	Log (pHandler, Common::ServerEvent::Trace, args...);
}

template <class... Args>
void Debug (EventHandler pHandler, const Args &... args)
{
	Log (pHandler, Common::ServerEvent::TraceDebug, args...);
}
} // namespace Log
} // namespace Project

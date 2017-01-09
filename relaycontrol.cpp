#include "relaycontrol.h"

RelayControl::RelayControl(byte writePin, bool initiallyOpen)
:m_WritePin(writePin)
,m_IsOpen(initiallyOpen)
{
	
}

void RelayControl::Setup()
{
    pinMode(m_WritePin, OUTPUT);
    SetOpen(m_IsOpen);  //make sure to write to the pin to set the initial state.
}

void RelayControl::Update()
{
	// read from the pin to get actual state ??
}

void RelayControl::SetOpen(bool open)
{
  m_IsOpen = open;
  digitalWrite(m_WritePin, m_IsOpen);
}

bool RelayControl::IsOpen() const
{
	return m_IsOpen;
}

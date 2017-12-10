// Copyright (C) 2017 Jérôme Leclercq
// This file is part of the "Erewhon Shared" project
// For conditions of distribution and use, see copyright notice in LICENSE

#pragma once

#ifndef EREWHON_CLIENT_STATES_LOGINSTATE_HPP
#define EREWHON_CLIENT_STATES_LOGINSTATE_HPP

#include <Client/States/StateData.hpp>
#include <NDK/State.hpp>
#include <NDK/Widgets.hpp>

namespace ewn
{
	class LoginState final : public Ndk::State
	{
		public:
			inline LoginState(StateData& stateData);
			~LoginState() = default;

		private:
			void Enter(Ndk::StateMachine& fsm) override;
			void Leave(Ndk::StateMachine& fsm) override;
			bool Update(Ndk::StateMachine& fsm, float elapsedTime) override;

			void OnConnectionPressed();

			void UpdateStatus(const Nz::String& status, const Nz::Color& color = Nz::Color::White);

			void LayoutWidgets();

			NazaraSlot(ServerConnection, OnLoginFailure, m_onLoginFailureSlot);
			NazaraSlot(ServerConnection, OnLoginSuccess, m_onLoginSuccess);

			StateData& m_stateData;
			Ndk::ButtonWidget* m_connectionButton;
			Ndk::CheckboxWidget* m_rememberCheckbox;
			Ndk::LabelWidget* m_loginLabel;
			Ndk::LabelWidget* m_passwordLabel;
			Ndk::LabelWidget* m_serverAddrLabel;
			Ndk::LabelWidget* m_statusLabel;
			Ndk::TextAreaWidget* m_loginArea;
			Ndk::TextAreaWidget* m_passwordArea;
			Ndk::TextAreaWidget* m_serverAddrArea;
			bool m_loginSucceeded;
			float m_loginAccumulator;
	};
}

#include <Client/States/LoginState.inl>

#endif // EREWHON_CLIENT_STATES_LOGINSTATE_HPP

// Copyright (C) 2017 Jérôme Leclercq
// This file is part of the "Erewhon Server" project
// For conditions of distribution and use, see copyright notice in LICENSE

#pragma once

#ifndef EREWHON_SERVER_PLAYERCONTROLLEDCOMPONENT_HPP
#define EREWHON_SERVER_PLAYERCONTROLLEDCOMPONENT_HPP

#include <Nazara/Math/Vector3.hpp>
#include <NDK/Component.hpp>

namespace ewn
{
	class PlayerControlledComponent : public Ndk::Component<PlayerControlledComponent>
	{
		public:
			inline PlayerControlledComponent();

			inline Nz::UInt64 GetLastInputTime() const;

			template<typename F> void ProcessInputs(F inputFunc);

			inline void PushInput(Nz::UInt64 inputTime, const Nz::Vector3f& direction, const Nz::Vector3f& rotation);

			static Ndk::ComponentIndex componentIndex;

		private:
			struct InputData
			{
				Nz::UInt64 serverTime;
				Nz::Vector3f direction;
				Nz::Vector3f rotation;
			};

			Nz::UInt64 m_lastInputTime;
			std::vector<InputData> m_inputs;
	};
}

#include <Server/Components/PlayerControlledComponent.inl>

#endif // EREWHON_SERVER_PLAYERCONTROLLEDCOMPONENT_HPP

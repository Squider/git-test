...

if(!steambansKey.empty())
{
  HttpClient::get(get_manager(), boost::bind(&BustedModuleImpl::on_steambans_partner_response, this, steamId, _1, _2),
	"", "/eilapsiensilmille/idlookup.php?key=" + steambansKey + "&id=" + steamId, "steambans.com");
  ++count;
}

...

void on_steambans_partner_response(const std::string &steamId,
  const std::string &cookies, const std::string &response)
{
  std::ofstream file("steambans_partner_response.html", std::ios::binary);
  file << response;

  if(response.find('1') != std::string::npos)
  {
	add_ban(steamId, "SteamBans", steambansAuthorized);
  }
  else if(response.find('2') != std::string::npos)
  {
	add_suspicion(steamId, "SteamBans");
  }
  else if(response.find('0') == std::string::npos)
  {
	std::cout << "busted.cpp: Error: Invalid partner response from SteamBans.\n";
  }

  add_response(steamId);
}

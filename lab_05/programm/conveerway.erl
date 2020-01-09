-module(conveerway).

-export([run_test/3, get_random_strings/3, get_random_string/2, controller/4, atob/0, tolower/0]).

run_test(String_amount, Length, Loop_amount) ->
  Time = erlang:timestamp(),
  register(controller, spawn(conveer_way, controller, [String_amount, Length, Loop_amount, Time])).

controller(_, _, 0, Time) ->
  Time1 = erlang:timestamp(),
  {ok, File} = file:open("out.txt", [append]),
  io:format(File, "~n~w", [timer:now_diff(Time1, Time)]),
  io:format("Test done!!! ~n");

controller(String_amount, Length, Loop_amount, Time) ->
  init_test(Length, String_amount, "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM"),
  Monitor1 = erlang:monitor(process, atob),
  receive
    {'DOWN', Monitor1, process, Pid, Reason} ->
%%      io:format("Loop finished!~n"),
      controller(String_amount, Length, Loop_amount - 1, Time)
  end.

init_test(String_length, String_Amount, AllowedChars) ->
  register(tolower, spawn(conveer_way, tolower, [])),
  register(atob, spawn(conveer_way, atob, [])),
  spawn(conveer_way, get_random_strings, [String_Amount, String_length, AllowedChars]).


get_random_strings(0, _, _) ->
  tolower ! finished,
  exit(normal);
get_random_strings(String_Amount, Length, AllowedChars) ->
  String = get_random_string(Length, AllowedChars),
%%  io:format("String: ~s ~n", [String]),
  tolower ! {string, String},
  get_random_strings(String_Amount - 1, Length, AllowedChars).


tolower() ->
  receive
    {string, String} ->
      String_new = string:to_lower(String),
%%      io:format("tolower: ~s | ~s ~n", [String, String_new]),
      atob ! {string, String_new},
      tolower();
    finished ->
      atob ! finished,
      exit(normal)
  end.


atob() ->
  receive
    {string, String} ->
      string:replace(String, "a", "b", all),
%%      io:format("atob: ~s | ~s ~n", [String, String_new]),
      atob();
    finished ->
      exit(normal)
  end.


get_random_string(Length, AllowedChar) ->
  lists:foldl(fun(_, Acc) ->
    [lists:nth(rand:uniform(length(AllowedChar)), AllowedChar)] ++ Acc end,
    [], lists:seq(1, Length)).




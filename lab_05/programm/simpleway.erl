-module(simple_way).
-author("User").

%% API
-export([test/3, get_random_string/2, get_random_strings/3, loop/3]).


test(Words_count, Word_leng, Loops) ->
%%  Time_begin = erlang:timestamp(),
%%  loop(Words_count, Word_leng, Loops),
%%  timer:now_diff(erlang:timestamp(), Time_begin).
  timer:tc(fun loop/3, [Words_count, Word_leng, Loops]).

loop(Words_count, Word_lenght, 0) ->
  ok;

loop(Words_count, Word_lenght, Loops) ->
  Strings = get_random_strings(Words_count, Word_lenght, "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM"),
  Strings1 = lists:map(fun string:to_lower/1, Strings),
  Func = fun(String) ->
    string:replace(String, "a", "b", all)
    end,
  Strings2 = lists:map(Func, Strings1),
  loop(Words_count, Word_lenght, Loops - 1).


get_random_strings(0, Length, AllowedChars) ->
  [];
get_random_strings(Count, Length, AllowedChars) ->
  lists:append([get_random_string(Length, AllowedChars)], get_random_strings(Count - 1, Length, AllowedChars)).


get_random_string(Length, AllowedChar) ->
  lists:foldl(fun(_, Acc) ->
    [lists:nth(rand:uniform(length(AllowedChar)), AllowedChar)] ++ Acc end,
    [], lists:seq(1, Length)).
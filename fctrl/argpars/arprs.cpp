
auto argpars::GetParams() ///< returns params from argv
{
    return params;
}
auto argpars::GetArgs() ///< returns args (taged "-" or "--") from argv
{
    return args;
}

argpars::argpars(int argc, char **argv)
{
    for (auto i = 0; i < argc; i++)
    {
        std::string cur_word = argv[i];
        auto length = cur_word.size();

        if (cur_word[0] == '-' && length > 1)
        {
            if (cur_word[1] == '-')
            {
                cur_word = cur_word.substr(2, length);
                args.push_back(cur_word);
            }
            else
            {
                cur_word = cur_word.substr(1, length);
                for (auto &&i : cur_word)
                {
                    std::string flag(1, i);
                    args.push_back(flag);
                }
            }
        }
        else
            params.push_back(cur_word);
    }
}

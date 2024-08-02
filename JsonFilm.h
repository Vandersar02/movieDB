#pragma once
#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"
#include <fstream>
#include <iostream>
#include <vector>
#include "Film.h"

using namespace rapidjson;
using namespace std;


vector<Film> DeserialiserFilms(const CStringA& jsonData)
{
    vector<Film> films;

    Document document;
    if (document.Parse(jsonData.GetString()).HasParseError()) {
        cout << "Erreur lors de l'analyse du JSON." << endl;
        return films;
    }

    if (!document.IsObject() || !document.HasMember("results") || !document["results"].IsArray()) {
        cout << "JSON invalide." << endl;
        return films;
    }

    const Value& results = document["results"];
    for (SizeType i = 0; i < results.Size(); i++) {
        const Value& filmData = results[i];

        if (!filmData.IsObject() || !filmData.HasMember("original_title") || !filmData.HasMember("overview") || !filmData.HasMember("poster_path") || !filmData.HasMember("vote_average")) {
            cout << "Données du film manquantes." << endl;
            continue;
        }

        const Value& title = filmData["original_title"];
        const Value& overview = filmData["overview"];
        const Value& posterPath = filmData["poster_path"];
        const Value& voteAverage = filmData["vote_average"];

        if (!title.IsString() || !overview.IsString() || !posterPath.IsString() || !voteAverage.IsDouble()) {
            cout << "Données du film invalides." << endl;
            continue;
        }

        Film film(title.GetString(), overview.GetString(), posterPath.GetString(), voteAverage.GetDouble());
        films.push_back(film);
    }

    return films;
}
